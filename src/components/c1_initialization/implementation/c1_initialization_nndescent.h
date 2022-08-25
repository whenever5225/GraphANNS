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
        /**
         * 这个是主函数，对吧。来个思路，分几步走：
         * 1，定义和初始化会用到的变量
         * 2，每个函数依次执行
         */
        std::vector<unsigned> sample_points(sample_num_);    // sample point id for evaluating graph quality
        std::vector<std::vector<unsigned>> knn_set(sample_num_);    // exact knn set of sample point id

        init_neighbor();    /* todo 有返回值不判断 */

        GenRandomID(sample_points.data(), num_, sample_points.size());    // generate random sample point id

        generate_sample_set(sample_points, knn_set);    // calculate exact knn set of sample point id

        // todo 自己改一下名字哈。主流程里，函数式表达挺好看的，对吧
        my_function_name(sample_points, knn_set);

        return CStatus();
    }

    CStatus refreshParam() override {
        for (size_t i = 0; i < num_; i++) {
            unsigned size = std::min((unsigned)graph_pool_[i].size(), out_degree_);
            for (unsigned j = 0; j < size; j++) {
                model_->graph_n_[i].emplace_back(Neighbor(graph_pool_[i][j].id_, graph_pool_[i][j].distance_));
            }

            std::vector<NeighborFlag>().swap(graph_pool_[i]);
            std::vector<unsigned>().swap(graph_nn_[NN_NEW][i]);
            std::vector<unsigned>().swap(graph_nn_[NN_OLD][i]);
            std::vector<unsigned>().swap(graph_nn_[RNN_NEW][i]);
            std::vector<unsigned>().swap(graph_nn_[RNN_OLD][i]);
        }

        std::vector<std::vector<NeighborFlag>>().swap(graph_pool_);
        std::vector<std::vector<unsigned >>().swap(graph_nn_[NN_NEW]);
        std::vector<std::vector<unsigned >>().swap(graph_nn_[NN_OLD]);
        std::vector<std::vector<unsigned >>().swap(graph_nn_[RNN_NEW]);
        std::vector<std::vector<unsigned >>().swap(graph_nn_[RNN_OLD]);
        return CStatus();
    }

protected:
    /**
     * initialize a random graph
     * @return
     */
    CStatus init_neighbor() {
        DistResType dist = 0;    // 不用反复构建了，对吧

        for (unsigned i = 0; i < num_; i++) {
            graph_nn_[NN_NEW][i].resize(nn_size_ * 2);
            GenRandomID(graph_nn_[NN_NEW][i].data(), num_, graph_nn_[NN_NEW][i].size());
            std::vector<unsigned> cur(nn_size_ + 1);
            GenRandomID(cur.data(), num_, cur.size());
            for (unsigned j = 0; j < nn_size_; j++) {
                unsigned id = cur[j];
                if (id == i) continue;
                dist_op_.calculate(data_ + i * dim_, data_ + id * dim_,
                                   dim_, dim_, dist);
                graph_pool_[i].emplace_back(NeighborFlag(id, dist, true));
            }
            graph_pool_[i].reserve(pool_size_ + 1);
        }

        return CStatus();
    }

    CStatus generate_sample_set(std::vector<unsigned> &s, std::vector<std::vector<unsigned>> &g) {
        DistResType dist = 0;

        for (unsigned i = 0; i < s.size(); i++) {
            std::vector<Neighbor> cur;
            cur.reserve(num_);    // todo 感觉是不是一样加一下比较规整
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

    float eval_quality(std::vector<unsigned> &ctrl_points,
                       std::vector<std::vector<unsigned>> &knn_set) {
        float mean_acc = 0;
        unsigned ctrl_points_size = ctrl_points.size();
        for (unsigned i = 0; i < ctrl_points_size; i++) {
            unsigned acc = 0;    // todo 这个是float类型的么？
            auto &g = graph_pool_[ctrl_points[i]];
            auto &v = knn_set[i];
            for (auto &j: g) {
                for (unsigned int k: v) {
                    if (j.id_ == k) {
                        acc++;
                        break;
                    }
                }
            }
            mean_acc += ((float) acc / (float) v.size());
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
    CStatus insert(unsigned pro_id, unsigned neigh_id, DistResType dist) {
        if (dist > graph_pool_[pro_id].back().distance_) return CStatus();
        for (auto &i: graph_pool_[pro_id]) {
            if (neigh_id == i.id_) return CStatus();
        }

        unsigned cur_pool_size = graph_pool_[pro_id].size();
        unsigned cur_min_size = std::min(cur_pool_size, pool_size_);

        // todo 看看这里能不能咋搞一下
        if (cur_pool_size <= pool_size_) {
            graph_pool_[pro_id].resize(cur_pool_size + 1);
        }

        InsertIntoPool(graph_pool_[pro_id].data(), cur_min_size, NeighborFlag(neigh_id, dist, true));
        return CStatus();
    }

    /**
     * Bi-directional insert. insert b and a into a's and b's neighbor pool, respectively
     * @param a
     * @param b
     * @return
     */
    CStatus bi_insert(unsigned a, unsigned b) {
        // todo two-way search？
        DistResType dist = 0;
        dist_op_.calculate(data_ + a * dim_, data_ + b * dim_,
                           dim_, dim_, dist);
        insert(a, b, dist);
        insert(b, a, dist);
        return CStatus();
    }

    CStatus join_neighbor() {
        for (unsigned n = 0; n < num_; n++) {
            for (unsigned const i: graph_nn_[NN_NEW][n]) {
                for (unsigned const j: graph_nn_[NN_NEW][n]) {
                    if (i < j) {
                        bi_insert(i, j);
                    }
                }
                for (unsigned const j: graph_nn_[NN_OLD][n]) {
                    if (i != j) {
                        bi_insert(i, j);
                    }
                }
            }
        }
        return CStatus();
    }

    /**
     *
     * @param pro_id
     * @param neigh_id
     * @param rnn_type : NN_NEW and so on
     * @return
     */
    CStatus generate_reverse_neighbor(unsigned pro_id, unsigned neigh_id, unsigned rnn_type) {
        /**
         * todo 这个不是一个unsigned类型就能结局的问题么，表示1，2，3，4
         * 一定要搞出点花样的话，可以尝试用 enum来传递。
         * 但是一般认为，typename是传递类型的
         */
        if (graph_nn_[rnn_type][neigh_id].size() < rnn_size_) {
            graph_nn_[rnn_type][neigh_id].push_back(pro_id);
        } else {
            unsigned int pos = random() % rnn_size_;
            graph_nn_[rnn_type][neigh_id][pos] = pro_id;
        }

        return CStatus();
    }

    CStatus shuffle_reverse_neighbor(std::vector<unsigned> rnn) const {
        if (rnn_size_ && rnn.size() > rnn_size_) {
            auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(rnn.begin(), rnn.end(),std::default_random_engine(seed));
            rnn.resize(rnn_size_);
        }
        return CStatus();
    }

    CStatus update_neighbor() {
        for (unsigned i = 0; i < num_; i++) {
            std::vector<unsigned>().swap(graph_nn_[NN_NEW][i]);
            std::vector<unsigned>().swap(graph_nn_[NN_OLD][i]);
        }

        for (unsigned n = 0; n < num_; ++n) {
            auto &nn_new = graph_nn_[NN_NEW][n];
            auto &nn_old = graph_nn_[NN_OLD][n];
            for (unsigned l = 0; l < pool_size_; ++l) {
                auto &neigh = graph_pool_[n][l];
                if (neigh.flag_) {
                    nn_new.push_back(neigh.id_);    // todo 这里的逻辑，明显还能继续抽象啊
                    if (neigh.distance_ > graph_pool_[neigh.id_].back().distance_) {
                        generate_reverse_neighbor(n, neigh.id_, NN_NEW);
                    }
                    neigh.flag_ = false;
                } else {
                    nn_old.push_back(neigh.id_);
                    if (neigh.distance_ > graph_pool_[neigh.id_].back().distance_) {
                        generate_reverse_neighbor(n, neigh.id_, NN_OLD);
                    }
                }
            }
        }

        for (unsigned i = 0; i < num_; ++i) {
            auto &nn_new = graph_nn_[NN_NEW][i];
            auto &nn_old = graph_nn_[NN_OLD][i];
            auto &rnn_new = graph_nn_[RNN_NEW][i];
            auto &rnn_old = graph_nn_[RNN_OLD][i];
            shuffle_reverse_neighbor(rnn_new);
            nn_new.insert(nn_new.end(), rnn_new.begin(), rnn_new.end());
            shuffle_reverse_neighbor(rnn_old);
            nn_old.insert(nn_old.end(), rnn_old.begin(), rnn_old.end());
            std::vector<unsigned>().swap(graph_nn_[RNN_NEW][i]);
            std::vector<unsigned>().swap(graph_nn_[RNN_OLD][i]);
        }

        return CStatus();
    }

    void my_function_name(std::vector<unsigned> &sample_points,
                          std::vector<std::vector<unsigned>> &knn_set) {
        for (unsigned it = 0; it < iter_; it++) {
            join_neighbor();    // neighbors join each other
            update_neighbor();    // update candidate neighbors for neighbors join
            float rc = eval_quality(sample_points, knn_set);    // evaluate graph quality for this iteration
            CGraph::CGRAPH_ECHO("iter: [%d], graph quality: [%f]", it, rc);
            if (rc >= graph_quality_threshold_)
                break;
        }
    }


protected:
    unsigned iter_ = 5;
    unsigned sample_num_ = 100;
    float graph_quality_threshold_ = 0.8;
    unsigned nn_size_ = 10;
    unsigned rnn_size_ = 5;
    unsigned pool_size_ = 20;
    std::vector<std::vector<NeighborFlag>> graph_pool_; // temp graph neighbor pool during nn-descent

    // todo 不建议有数字哈，比如 4，就不太清楚干什么的哈
    std::vector<std::vector<unsigned>> graph_nn_[MAX_NN_TYPE_SIZE]; // new, old, reverse new, and reverse old graph neighbors
};

#endif //GRAPHANNS_C1_INITIALIZATION_NNDESCENT_H
