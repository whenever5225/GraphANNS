/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c1_initialization_vamana.h
@Time: 2022/3/26 9:38 PM
@Desc: randomly initialize a graph index (like 'Vamana' algorithm in DiskANN)
***************************/

#ifndef GRAPHANNS_C1_INITIALIZATION_VAMANA_H
#define GRAPHANNS_C1_INITIALIZATION_VAMANA_H

#include "../c1_initialization_basic.h"
#include "../../../elements/nodes/param_nodes/param_include.h"
#include "../../../utils/utils.h"

class C1InitializationVamana : public C1InitializationBasic {
public:
    DAnnFuncType prepareParam() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        if (nullptr == g_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        num_ = g_param->num;
        dim_ = g_param->dim;
        data_ = g_param->data;
        out_degree_ = g_param->k_init_graph;
        g_param->graph_n.reserve(num_);

        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        graph_neigh_.clear();
        graph_neigh_.reserve(out_degree_);
        std::vector<unsigned> neighbor_id(out_degree_);
        GenRandomID(neighbor_id.data(), num_, out_degree_);
        for (const unsigned int &id: neighbor_id) {
            if (id != cur_num_) {
                graph_neigh_.emplace_back(id);
            }
        }

        return CStatus();
    }

    CStatus refreshParam() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param);
        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(g_param);
            g_param->graph_m.emplace_back(graph_neigh_);
        }
        return CStatus();
    }

    CBool isHold() override {
        cur_num_++;
        return cur_num_ < num_;
    }

protected:
    std::vector<unsigned> graph_neigh_;   // temp neighbor
};

#endif //GRAPHANNS_C1_INITIALIZATION_VAMANA_H
