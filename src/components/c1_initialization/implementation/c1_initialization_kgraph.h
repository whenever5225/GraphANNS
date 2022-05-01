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
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY);
        if (nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        num_ = t_param->num;
        dim_ = t_param->dim;
        data_ = t_param->data;
        out_degree_ = t_param->k_init_graph;
        t_param->graph_n.reserve(num_);

        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        graph_neigh_.clear();
        graph_neigh_.reserve(out_degree_);
        std::vector<unsigned> neighbor_id(out_degree_);
        GenRandomID(neighbor_id.data(), num_, out_degree_);
        for (const unsigned int &id: neighbor_id) {
            if (id != cur_num_) {
                DistResType dist = 0;
                dist_op_.calculate(data_ + (id * dim_),
                                  data_ + cur_num_ * dim_,
                                  dim_, dim_, dist);
                graph_neigh_.emplace_back(id, dist);
            }
        }

        return CStatus();
    }

    CStatus refreshParam() override {
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(t_param)
        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(t_param)
            t_param->graph_n.emplace_back(graph_neigh_);
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
