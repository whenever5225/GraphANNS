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

class C7RoutingKGraph : public C7RoutingBasic {
public:
    DAnnFuncType prepareParam() override {
        auto *s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY)
        if (nullptr == s_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        num_ = s_param->num;
        dim_ = s_param->dim;
        data_ = s_param->data;
        search_L_ = s_param->search_L;
        K_ = s_param->top_k;
        query_ = s_param->query;
        query_id_ = s_param->query_id;
        return DAnnFuncType::ANN_SEARCH;
    }

    CStatus search() override {
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY);
        auto s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY);
        if (nullptr == t_param || nullptr == s_param) {
            CGRAPH_RETURN_ERROR_STATUS("C7RoutingKGraph search get param failed")
        }

        std::vector<char> flags(num_, 0);
        res_.clear();

        unsigned k = 0;
        while (k < (int) search_L_) {
            unsigned nk = search_L_;

            if (s_param->sp[k].flag_) {
                s_param->sp[k].flag_ = false;
                unsigned n = s_param->sp[k].id_;

                for (unsigned m = 0; m < t_param->graph_m[n].size(); ++m) {
                    unsigned id = t_param->graph_m[n][m];

                    if (flags[id]) continue;
                    flags[id] = 1;

                    DistResType dist = 0;
                    dist_op_.calculate(query_ + (query_id_ * dim_),
                                      data_ + id * dim_, dim_, dim_, dist);

                    if (dist >= s_param->sp[search_L_ - 1].distance_) continue;
                    NeighborFlag nn(id, dist, true);
                    int r = InsertIntoPool(s_param->sp.data(), search_L_, nn);

                    if (r < nk) nk = r;
                }
            }
            nk <= k ? (k = nk) : (++k);
        }

        res_.reserve(K_);
        for (size_t i = 0; i < K_; i++) {
            res_.push_back(s_param->sp[i].id_);
        }
        return CStatus();
    }

    CStatus refreshParam() override {
        auto s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(s_param)

        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(s_param)
            s_param->results.push_back(res_);
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C7_ROUTING_KGRAPH_H
