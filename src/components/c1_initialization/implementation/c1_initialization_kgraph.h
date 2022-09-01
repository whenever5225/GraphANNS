/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c1_initialization_kgraph.h
@Time: 2022/4/4 4:51 PM
@Desc: randomly initialize a graph index (like 'KGraph' algorithm)
***************************/

#ifndef GRAPHANNS_C1_INITIALIZATION_KGRAPH_H
#define GRAPHANNS_C1_INITIALIZATION_KGRAPH_H

#include "../c1_initialization_basic.h"

class C1InitializationKGraph : public C1InitializationBasic {
public:
    DAnnFuncType prepareParam() override {
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY);
        model_ = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        if (nullptr == model_ || nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }

        num_ = model_->train_meta_modal1_.num;
        dim1_ = model_->train_meta_modal1_.dim;
        dim2_ = model_->train_meta_modal2_.dim;
        data_modal1_ = model_->train_meta_modal1_.data;
        data_modal2_ = model_->train_meta_modal2_.data;
        out_degree_ = t_param->k_init_graph;
        model_->graph_n_.reserve(num_);
        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        graph_neigh_.clear();
        graph_neigh_.reserve(out_degree_);
        std::vector<IDType> neighbor_id(out_degree_);
        GenRandomID(neighbor_id.data(), num_, out_degree_);
        for (const IDType &id: neighbor_id) {
            if (id != cur_num_) {
                DistResType dist = 0;
                dist_op_.calculate(data_modal1_ + (id * dim1_),
                                  data_modal1_ + cur_num_ * dim1_,
                                  dim1_, dim1_,
                                  data_modal2_ + (id * dim2_),
                                  data_modal2_ + cur_num_ * dim2_,
                                  dim2_, dim2_, dist);
                graph_neigh_.emplace_back(id, dist);
            }
        }

        return CStatus();
    }

    CStatus refreshParam() override {
        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(model_)
            model_->graph_n_.emplace_back(graph_neigh_);
        }
        return CStatus();
    }

    CBool isHold() override {
        cur_num_++;
        return cur_num_ < num_;
    }

protected:
    std::vector<Neighbor> graph_neigh_;   // temp neighbor
};

#endif //GRAPHANNS_C1_INITIALIZATION_KGRAPH_H
