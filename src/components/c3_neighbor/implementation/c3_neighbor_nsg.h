/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c3_neighbor_nsg.h
@Time: 2022/4/7 5:20 PM
@Desc: edge selection by RNG (a strategy that considers neighbor distribution and is applied to 'NSG', 'HNSW', etc.)
***************************/

#ifndef GRAPHANNS_C3_NEIGHBOR_NSG_H
#define GRAPHANNS_C3_NEIGHBOR_NSG_H

#include "../c3_neighbor_basic.h"

class C3NeighborNSG : public C3NeighborBasic {
public:
    DAnnFuncType prepareParam() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNpgTrain, GA_ALG_NPG_TRAIN_PARAM)
        if (nullptr == g_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        dim_ = g_param->dim;
        data_ = g_param->data;
        cur_id_ = g_param->cur_id;
        C_ = g_param->C_neighbor;
        R_ = g_param->R_neighbor;

        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param)

        unsigned start = 0;
        std::sort(g_param->pool.begin(), g_param->pool.end());
        result_.clear();
        if (g_param->pool[start].id_ == cur_id_) start++;
        result_.push_back(g_param->pool[start]);

        while (result_.size() < R_ && (++start) < g_param->pool.size() &&
               start < C_) {
            auto &p = g_param->pool[start];
            unsigned occlude = false;
            for (auto &t: result_) {
                if (p.id_ == t.id_) {
                    occlude = true;
                    break;
                }
                DistResType djk = 0;
                dist_op_.calculate(data_ + (t.id_ * dim_),
                                  data_ + p.id_ * dim_, dim_, dim_, djk);
                if (djk < p.distance_) {
                    occlude = true;
                    break;
                }
            }
            if (!occlude) result_.push_back(p);
        }
        return CStatus();
    }

    CStatus refreshParam() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param);
        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(g_param);
            g_param->cut_graph.push_back(result_);
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C3_NEIGHBOR_NSG_H
