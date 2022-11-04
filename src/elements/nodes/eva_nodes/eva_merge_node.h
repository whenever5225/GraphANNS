/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: eva_merge_node.h
@Time: 2022/11/1 6:59 PM
@Desc: merge multichannel results
***************************/

#ifndef GRAPHANNS_EVA_MERGE_NODE_H
#define GRAPHANNS_EVA_MERGE_NODE_H

#include "../../elements_define.h"

class EvaMergeNode : public CGraph::GNode {
public:
    CStatus init() override {
        auto m_param = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(m_param)
        num_ = m_param->search_meta_modal1_.num;

        return CStatus();
    }
    CStatus run() override {
        auto *s_param = CGRAPH_GET_GPARAM(AlgParamBasic, GA_ALG_PARAM_BASIC_KEY);
        if (nullptr == s_param) {
            CGRAPH_RETURN_ERROR_STATUS("EvaMergeNode run get param failed")
        }
        top_k_ = s_param->top_k;
        std::set<IDType> modal1_set, modal2_set, res_set;
        for (IDType i = 0; i < num_; i++) {
            modal1_set.clear();
            modal2_set.clear();
            modal1_set.insert(s_param->results_modal1[i].begin(), s_param->results_modal1[i].end());
            modal2_set.insert(s_param->results_modal2[i].begin(), s_param->results_modal2[i].end());
            std::vector<IDType> res_intersection;
            std::set_intersection(modal1_set.begin(), modal1_set.end(), modal2_set.begin(),
                                  modal2_set.end(),std::insert_iterator<std::vector<IDType>>(
                            res_intersection, res_intersection.begin()));
            unsigned p = 0;
            res_set.clear();
            res_set.insert(res_intersection.begin(), res_intersection.end());
            while (res_set.size() < top_k_) {
                res_set.insert(s_param->results_modal1[i].begin() + p,
                               s_param->results_modal1[i].begin() + p + 1);
                p++;
            }
            res_intersection.clear();
            res_intersection.insert(res_intersection.begin(), res_set.begin(), res_set.end());
            s_param->results.emplace_back(res_intersection);
            s_param->results[i].resize(top_k_);
        }

        return CStatus();
    }

private:
    IDType num_;
    unsigned top_k_;
};

#endif //GRAPHANNS_EVA_MERGE_NODE_H
