/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c1_initialization_nndescent.h
@Time: 2022/5/21 7:20 PM
@Desc: initialize a graph index with NNDescent (like 'NSG' algorithm)
***************************/

#ifndef GRAPHANNS_C1_INITIALIZATION_NNDESCENT_H
#define GRAPHANNS_C1_INITIALIZATION_NNDESCENT_H

#include "../c1_initialization_basic.h"
#include <algorithm>

static const unsigned NN_NEW = 0;     // new graph neighbors
static const unsigned NN_OLD = 1;     // old graph neighbors
static const unsigned RNN_NEW = 2;    // reverse new graph neighbors
static const unsigned RNN_OLD = 3;    // reverse old graph neighbors
static const unsigned MAX_NN_TYPE_SIZE = 4;

class C1InitializationNNDescent : public C1InitializationBasic {
public:
    DAnnFuncType prepareParam() override {
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        model_ = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY)
        if (nullptr == model_ || nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }

        num_ = model_->train_meta_.num;
        dim_ = model_->train_meta_.dim;
        data_ = model_->train_meta_.data;
        model_->graph_n_.reserve(num_);
        out_degree_ = t_param->k_init_graph;
        nn_size_ = t_param->nn_size;
        rnn_size_ = t_param->rnn_size;
        pool_size_ = t_param->pool_size;
        iter_ = t_param->iter;
        sample_num_ = t_param->sample_num;
        graph_quality_threshold_ = t_param->graph_quality_threshold;
        graph_pool_.reserve(num_);
        graph_nn_[NN_NEW].reserve(num_);
        graph_nn_[NN_OLD].reserve(num_);
        graph_nn_[RNN_NEW].reserve(num_);
        graph_nn_[RNN_OLD].reserve(num_);

        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        std::vector<IDType> sample_points(sample_num_);    // sample point id for evaluating graph quality
        std::vector<std::vector<IDType>> knn_set(sample_num_);    // exact knn set of sample point id

        CStatus status = init_neighbor();

        GenRandomID(sample_points.data(), num_, sample_points.size());    // generate random sample point id

        status += generate_sample_set(sample_points, knn_set);    // calculate exact knn set of sample point id

        status += nn_descent(sample_points, knn_set);    // update points' neighbors by nn-descent

        return status;
    }

    CStatus refreshParam() override {
        for (size_t i = 0; i < num_; i++) {
            unsigned size = std::min((unsigned) graph_pool_[i].size(), out_degree_);
            for (unsigned j = 0; j < size; j++) {
                model_->graph_n_[i].emplace_back(Neighbor(graph_pool_[i][j].id_, graph_pool_[i][j].distance_));
            }

            std::vector<NeighborFlag>().swap(graph_pool_[i]);
            std::vector<IDType>().swap(graph_nn_[NN_NEW][i]);
            std::vector<IDType>().swap(graph_nn_[NN_OLD][i]);
            std::vector<IDType>().swap(graph_nn_[RNN_NEW][i]);
            std::vector<IDType>().swap(graph_nn_[RNN_OLD][i]);
        }

        std::vector<std::vector<NeighborFlag>>().swap(graph_pool_);
        std::vector<std::vector<IDType >>().swap(graph_nn_[NN_NEW]);
        std::vector<std::vector<IDType >>().swap(graph_nn_[NN_OLD]);
        std::vector<std::vector<IDType >>().swap(graph_nn_[RNN_NEW]);
        std::vector<std::vector<IDType >>().swap(graph_nn_[RNN_OLD]);
        return CStatus();
    }

protected:
    /**
     * initialize a random graph
     * @return
     */
    CStatus init_neighbor() {
        DistResType dist = 0;

        for (IDType i = 0; i < num_; i++) {
            graph_nn_[NN_NEW][i].resize(nn_size_ * 2);
            GenRandomID(graph_nn_[NN_NEW][i].data(), num_, graph_nn_[NN_NEW][i].size());
            std::vector<IDType> cur(nn_size_ + 1);
            GenRandomID(cur.data(), num_, cur.size());
            for (unsigned j = 0; j < nn_size_; j++) {
                IDType id = cur[j];
                if (id == i) continue;
                dist_op_.calculate(data_ + i * dim_, data_ + id * dim_,
                                   dim_, dim_, dist);
                graph_pool_[i].emplace_back(NeighborFlag(id, dist, true));
            }
            graph_pool_[i].reserve(pool_size_ + 1);
        }

        return CStatus();
    }

    CStatus generate_sample_set(std::vector<IDType> &s, std::vector<std::vector<IDType>> &g) {
        DistResType dist = 0;

        for (unsigned i = 0; i < s.size(); i++) {
            std::vector<Neighbor> cur;
            cur.reserve(num_);
            for (unsigned j = 0; j < num_; j++) {
                dist_op_.calculate(data_ + s[i] * dim_, data_ + j * dim_,
                                   dim_, dim_, dist);
                cur.emplace_back(j, dist);
            }

            std::partial_sort(cur.begin(), cur.begin() + sample_num_, cur.end());
            for (unsigned j = 0; j < sample_num_; j++) {
                g[i].emplace_back(cur[j].id_);
            }
        }

        return CStatus();
    }

    float eval_quality(const std::vector<IDType> &ctrl_points,
                       const std::vector<std::vector<IDType>> &knn_set) {
        float mean_acc = 0;
        unsigned ctrl_points_size = ctrl_points.size();
        for (unsigned i = 0; i < ctrl_points_size; i++) {
            unsigned acc = 0;
            for (auto &j: graph_pool_[ctrl_points[i]]) {
                for (IDType k: knn_set[i]) {
                    if (j.id_ == k) {
                        acc++;
                        break;
                    }
                }
            }
            mean_acc += ((float) acc / (float) knn_set[i].size());
        }

        return mean_acc / (float) ctrl_points_size;
    }

    /**
     * insert neigh_id into pro_id's neighbor pool
     * @param pro_id
     * @param neigh_id
     * @param dist
     * @return
     */
    CStatus insert(IDType pro_id, IDType neigh_id, DistResType dist) {
        if (dist > graph_pool_[pro_id].back().distance_) return CStatus();
        for (auto &i: graph_pool_[pro_id]) {
            if (neigh_id == i.id_) return CStatus();
        }

        unsigned cur_pool_size = graph_pool_[pro_id].size();
        unsigned cur_min_size = std::min(cur_pool_size, pool_size_);
        graph_pool_[pro_id].resize(cur_min_size + 1);

        InsertIntoPool(graph_pool_[pro_id].data(), cur_min_size,
                       NeighborFlag(neigh_id, dist, true));

        return CStatus();
    }

    /**
     * Bi-directional insert. insert b and a into a's and b's neighbor pool, respectively
     * @param a
     * @param b
     * @return
     */
    CStatus bi_insert(IDType a, IDType b) {
        DistResType dist = 0;
        dist_op_.calculate(data_ + a * dim_, data_ + b * dim_,
                           dim_, dim_, dist);
        insert(a, b, dist);
        insert(b, a, dist);
        return CStatus();
    }

    /**
     * obtain a new id j from nn_new or nn_old,
     * satisfying cur_id and j have not been inserted each other
     * @param pro_id
     * @param cur_id
     * @param nn_type: NN_NEW and NN_OLD
     * @return
     */
    CStatus mutual_insert(IDType pro_id, IDType cur_id, unsigned nn_type) {
        for (IDType const j: graph_nn_[nn_type][pro_id]) {
            if ((NN_NEW == nn_type && cur_id < j)
                 || (NN_OLD == nn_type && cur_id != j)) {
                bi_insert(cur_id, j);
            }
        }
        return CStatus();
    }

    CStatus join_neighbor() {
        CStatus status;
        for (IDType n = 0; n < num_; n++) {
            for (unsigned const i: graph_nn_[NN_NEW][n]) {
                status += mutual_insert(n, i, NN_NEW);
                status += mutual_insert(n, i, NN_OLD);
            }
        }
        return status;
    }

    /**
     *
     * @param pro_id
     * @param neigh_id
     * @param rnn_type : RNN_NEW and RNN_OLD
     * @return
     */
    CStatus generate_reverse_neighbor(IDType pro_id, IDType neigh_id, unsigned rnn_type) {
        if (graph_nn_[rnn_type][neigh_id].size() < rnn_size_) {
            graph_nn_[rnn_type][neigh_id].emplace_back(pro_id);
        } else {
            unsigned int pos = random() % rnn_size_;
            graph_nn_[rnn_type][neigh_id][pos] = pro_id;
        }

        return CStatus();
    }

    CStatus shuffle_reverse_neighbor(std::vector<IDType> rnn) const {
        if (rnn_size_ && rnn.size() > rnn_size_) {
            auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(rnn.begin(), rnn.end(), std::default_random_engine(seed));
            rnn.resize(rnn_size_);
        }
        return CStatus();
    }

    /**
     * generate pro_id's nn_new, nn_old, rnn_new, and rnn_old,
     * according to pro_id's neighbor neigh_id in pool
     * @param pro_id
     * @param neigh_id
     * @return
     */
    CStatus generate_neighbor(IDType pro_id, IDType neigh_id) {
        auto &neigh = graph_pool_[pro_id][neigh_id];
        unsigned nn_type;
        unsigned rnn_type;
        if (neigh.flag_) {
            nn_type = NN_NEW;
            rnn_type = RNN_NEW;
            neigh.flag_ = false;
        } else {
            nn_type = NN_OLD;
            rnn_type = RNN_OLD;
        }
        graph_nn_[nn_type][pro_id].emplace_back(neigh.id_);

        if (neigh.distance_ > graph_pool_[neigh.id_].back().distance_) {
            generate_reverse_neighbor(pro_id, neigh.id_, rnn_type);
        }

        return CStatus();
    }

    /**
     * insert pro_id's reverse neighbor (rnn_type) into nn_type neighbor
     * @param pro_id
     * @param nn_type: NN_NEW and NN_OLD
     * @param rnn_type: RNN_NEW and RNN_OLD
     * @return
     */
    CStatus insert_reverse_neighbor(IDType pro_id, unsigned nn_type, unsigned rnn_type) {
        auto &nn = graph_nn_[nn_type][pro_id];
        auto &rnn = graph_nn_[rnn_type][pro_id];
        CStatus status = shuffle_reverse_neighbor(rnn);
        nn.insert(nn.end(), rnn.begin(), rnn.end());
        std::vector<IDType>().swap(rnn);
        return status;
    }

    CStatus update_neighbor() {
        CStatus status;
        for (IDType i = 0; i < num_; i++) {
            std::vector<unsigned>().swap(graph_nn_[NN_NEW][i]);
            std::vector<unsigned>().swap(graph_nn_[NN_OLD][i]);
        }

        for (IDType i = 0; i < num_; i++) {
            for (unsigned l = 0; l < pool_size_; ++l) {
                status += generate_neighbor(i, l);
            }
            status += insert_reverse_neighbor(i, NN_NEW, RNN_NEW);
            status += insert_reverse_neighbor(i, NN_OLD, RNN_OLD);
        }

        return status;
    }

    /**
     * iteratively optimize vertices' neighbors
     * @param sample_points
     * @param knn_set
     * @return
     */
    CStatus nn_descent(std::vector<IDType> &sample_points,
                    std::vector<std::vector<IDType>> &knn_set) {
        CStatus status;
        for (unsigned it = 0; it < iter_; it++) {
            status += join_neighbor();    // neighbors join each other

            status += update_neighbor();    // update candidate neighbors for neighbors join

            float rc = eval_quality(sample_points, knn_set);    // evaluate graph quality for this iteration
            CGraph::CGRAPH_ECHO("iter: [%d], graph quality: [%f]", it, rc);
            if (rc >= graph_quality_threshold_)
                break;
        }

        return status;
    }


protected:
    unsigned iter_ = 5;
    unsigned sample_num_ = 100;
    float graph_quality_threshold_ = 0.8;
    unsigned nn_size_ = 10;
    unsigned rnn_size_ = 5;
    unsigned pool_size_ = 20;
    std::vector<std::vector<NeighborFlag>> graph_pool_; // temp graph neighbor pool during nn-descent

    std::vector<std::vector<IDType>> graph_nn_[MAX_NN_TYPE_SIZE]; // new, old, reverse new, and reverse old graph neighbors
};

#endif //GRAPHANNS_C1_INITIALIZATION_NNDESCENT_H
