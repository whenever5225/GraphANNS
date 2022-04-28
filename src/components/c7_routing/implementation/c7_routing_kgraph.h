/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c7_routing_kgraph.h
@Time: 2022/4/8 8:37 AM
@Desc: greedy route (like 'KGraph' algorithm)
***************************/

#ifndef GRAPHANNS_C7_ROUTING_KGRAPH_H
#define GRAPHANNS_C7_ROUTING_KGRAPH_H

#include "../c7_routing_basic.h"
#include "../../../elements/nodes/param_nodes/param_include.h"
#include "../../../utils/utils.h"

class C7RoutingKGraph : public C7RoutingBasic {
public:
    DAnnFuncType prepareParam() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        if (nullptr == g_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        num_ = g_param->num;
        dim_ = g_param->dim;
        data_ = g_param->data;
        search_L_ = g_param->search_L;
        K_ = g_param->top_k;
        query_ = g_param->query;
        query_id_ = g_param->query_id;
        return DAnnFuncType::ANN_SEARCH;
    }

    CStatus search() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param)

        std::vector<char> flags(num_, 0);
        res_.clear();

        unsigned k = 0;
        while (k < (int) search_L_) {
            unsigned nk = search_L_;

            if (g_param->sp[k].flag_) {
                g_param->sp[k].flag_ = false;
                unsigned n = g_param->sp[k].id_;

                for (unsigned m = 0; m < g_param->graph_m[n].size(); ++m) {
                    unsigned id = g_param->graph_m[n][m];

                    if (flags[id])continue;
                    flags[id] = 1;

                    DistResType dist = 0;
                    DistCalcType distOper;
                    distOper.calculate(query_ + (query_id_ * dim_),
                                      data_ + id * dim_, dim_, dim_, dist);

                    if (dist >= g_param->sp[search_L_ - 1].distance_) continue;
                    NeighborFlag nn(id, dist, true);
                    int r = InsertIntoPool(g_param->sp.data(), search_L_, nn);

                    if (r < nk) nk = r;
                }
            }
            nk <= k ? (k = nk) : (++k);
        }

        res_.reserve(K_);
        for (size_t i = 0; i < K_; i++) {
            res_.push_back(g_param->sp[i].id_);
        }
        return CStatus();
    }

    CStatus refreshParam() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param);
        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(g_param);
            g_param->results.push_back(res_);
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C7_ROUTING_KGRAPH_H
