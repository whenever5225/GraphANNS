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
        auto *s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY);
        auto *a_param = CGRAPH_GET_GPARAM(AlgParamBasic, GA_ALG_PARAM_BASIC_KEY);
        model_ = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        if (nullptr == model_ || nullptr == s_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }

        num_ = model_->train_meta_modal1_.num;
        dim1_ = model_->train_meta_modal1_.dim;
        dim2_ = model_->train_meta_modal2_.dim;
        data_modal1_ = model_->train_meta_modal1_.data;
        data_modal2_ = model_->train_meta_modal2_.data;
        search_L_ = s_param->search_L;
        K_ = a_param->top_k;
        query_id_ = s_param->query_id;
        query_modal1_ = model_->search_meta_modal1_.data;
        query_modal2_ = model_->search_meta_modal2_.data;
        return DAnnFuncType::ANN_SEARCH;
    }

    CStatus search() override {
        auto s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY);
        if (nullptr == s_param) {
            CGRAPH_RETURN_ERROR_STATUS("C7RoutingKGraph search get param failed")
        }

        std::vector<char> flags(num_, 0);
        res_.clear();

        unsigned k = 0;
        while (k < (int) search_L_) {
            unsigned nk = search_L_;

            if (s_param->sp[k].flag_) {
                s_param->sp[k].flag_ = false;
                IDType n = s_param->sp[k].id_;

                for (unsigned m = 0; m < model_->graph_m_[n].size(); ++m) {
                    IDType id = model_->graph_m_[n][m];

                    if (flags[id]) continue;
                    flags[id] = 1;

                    DistResType dist = 0;
                    dist_op_.calculate(query_modal1_ + (query_id_ * dim1_),
                                      data_modal1_ + id * dim1_,
                                      dim1_, dim1_,
                                       query_modal2_ + (query_id_ * dim2_),
                                       data_modal2_ + id * dim2_,
                                      dim2_, dim2_, dist);

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
        auto a_param = CGRAPH_GET_GPARAM(AlgParamBasic, GA_ALG_PARAM_BASIC_KEY);
        CGRAPH_ASSERT_NOT_NULL(a_param)

        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(a_param)
            a_param->results.push_back(res_);
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C7_ROUTING_KGRAPH_H
