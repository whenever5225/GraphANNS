/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: eva_recall_node.h
@Time: 2022/4/8 4:31 PM
@Desc: calculate recall rate
***************************/

#ifndef GRAPHANNS_EVA_RECALL_NODE_H
#define GRAPHANNS_EVA_RECALL_NODE_H

#include <iterator>
#include "../../elements_define.h"

class EvaRecallNode : public CGraph::GNode {
public:
    CStatus init() override {

        auto m_param = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(m_param)
        CStatus status = m_param->eva_meta_.load(Params.GA_ALG_GROUND_TRUTH_PATH_, 0);
        if (!status.isOK()) {
            CGRAPH_RETURN_ERROR_STATUS("EvaRecallNode init load param failed")
        }

        gt_num_ = m_param->eva_meta_.num;
        return status;
    }

    CStatus run() override {
        auto *m_param = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY)
        auto *s_param = CGRAPH_GET_GPARAM(AlgParamBasic, GA_ALG_PARAM_BASIC_KEY);
        if (nullptr == m_param || nullptr == s_param) {
            CGRAPH_RETURN_ERROR_STATUS("EvaRecallNode run get param failed")
        }

        unsigned top_k = s_param->top_k;
        unsigned gt_k = Params.gt_k_;
        int cnt = 0;
        std::set<IDType> gt, res;
        for (unsigned i = 0; i < gt_num_; i++) {
            if (s_param->results[i].empty()) continue;
            gt_look_num_ = (Params.is_multi_res_equal_ ? m_param->eva_meta_.vec[i].size() : gt_k);
            gt.clear();
            res.clear();
            gt.insert(m_param->eva_meta_.vec[i].begin(), m_param->eva_meta_.vec[i].begin() + gt_look_num_);
            res.insert(s_param->results[i].begin(), s_param->results[i].begin() + top_k);
            std::vector<IDType> res_intersection;
            std::set_intersection(gt.begin(), gt.end(), res.begin(), res.end(),
                                  std::insert_iterator<std::vector<IDType>>(res_intersection,
                                          res_intersection.begin()));
            cnt += (res_intersection.size() >= gt_k ? (int) gt_k : (int) res_intersection.size());
        }

        float acc = (float) cnt / (float) (gt_num_ * gt_k);
        printf("[EVA] %d NN accuracy for top%d: %f\n", gt_k, top_k, acc);
        return CStatus();
    }

private:
    unsigned gt_num_ = 0;
    unsigned gt_look_num_ = 0;
};

#endif //GRAPHANNS_EVA_RECALL_NODE_H
