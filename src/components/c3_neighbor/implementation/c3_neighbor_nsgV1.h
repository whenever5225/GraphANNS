/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c3_neighbor_nsgv1.h
@Time: 2022/4/7 5:20 PM
@Desc: edge selection by RNG (a strategy that considers neighbor distribution and is applied to 'NSG', 'HNSW', etc.)
***************************/

#ifndef GRAPHANNS_C3_NEIGHBOR_NSGV1_H
#define GRAPHANNS_C3_NEIGHBOR_NSGV1_H

#include "../../../elements/elements.h"
#include "../../../utils/utils.h"
#include "../c3_neighbor_basic.h"

class C3NeighborNSGV1 : public C3NeighborBasic {
public:
    DAnnFuncType prepareParam() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        if (nullptr == g_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        dim_ = g_param->dim;
        data_ = g_param->data;
        num_ = g_param->num;
        C_ = g_param->C_neighbor;
        R_ = g_param->R_neighbor;

        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);

        CGRAPH_ASSERT_NOT_NULL(g_param)

        for (unsigned i = 0; i < num_; i++) {
            unsigned start = 0;
            std::sort(g_param->pool_m[i].begin(), g_param->pool_m[i].end());
            std::vector<Neighbor> result;
            if (g_param->pool_m[i][start].id_ == i) start++;
            result.push_back(g_param->pool_m[i][start]);

            while (result.size() < R_
                   && (++start) < g_param->pool_m[i].size() && start < C_) {
                auto &p = g_param->pool_m[i][start];
                bool occlude = false;
                for (const auto &res: result) {
                    if (p.id_ == res.id_) {
                        occlude = true;
                        break;
                    }
                    DistResType djk = 0;
                    DistCalcType eucDist;
                    eucDist.calculate(data_ + (res.id_ * dim_),
                                      data_ + p.id_ * dim_,
                                      dim_, dim_, djk);
                    if (djk < p.distance_) {
                        occlude = true;
                        break;
                    }
                }
                if (!occlude) result.push_back(p);
            }

            {
                CGRAPH_PARAM_WRITE_CODE_BLOCK(g_param);
                g_param->cut_graph.push_back(result);
            }
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C3_NEIGHBOR_NSGV1_H
