/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: eva_recall_node.h
@Time: 2022/4/8 4:31 PM
@Desc: calculate recall rate
***************************/

#ifndef GRAPHANNS_EVA_RECALL_NODE_H
#define GRAPHANNS_EVA_RECALL_NODE_H

#include "../../elements.h"
#include "../../elements_define.h"

class EvaRecallNode : public CGraph::GNode {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(EvaParam, GA_ALG_NPG_EVA_PARAM_KEY);
        if (!status.isOK()) {
            CGRAPH_RETURN_ERROR_STATUS("EvaRecallNode init create param failed")
        }

        auto *e_param = CGRAPH_GET_GPARAM(EvaParam, GA_ALG_NPG_EVA_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(e_param)
        status = e_param->load(GA_ALG_GROUNDTRUTH_PATH);
        if (!status.isOK()) {
            CGRAPH_RETURN_ERROR_STATUS("EvaRecallNode init load param failed")
        }

        gt_num_ = e_param->num;
        gt_dim_ = e_param->dim;
        return status;
    }

    CStatus run() override {
        auto *e_param = CGRAPH_GET_GPARAM(EvaParam, GA_ALG_NPG_EVA_PARAM_KEY);
        auto *s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY);
        if (nullptr == e_param || nullptr == s_param) {
            CGRAPH_RETURN_ERROR_STATUS("EvaRecallNode run get param failed")
        }

        top_k_ = s_param->top_k;
        int cnt = 0;
        for (unsigned i = 0; i < gt_num_; i++) {
            if (s_param->results[i].empty()) continue;
            for (unsigned j = 0; j < top_k_; j++) {
                unsigned k = 0;
                for (; k < top_k_; k++) {
                    if (s_param->results[i][j] == e_param->data[i * gt_dim_ + k])
                        break;
                }
                if (k == top_k_)
                    cnt++;
            }
        }

        float acc = 1 - (float) cnt / (float) (gt_num_ * top_k_);
        CGraph::CGRAPH_ECHO("%d NN accuracy: %f", top_k_, acc);
        return CStatus();
    }

private:
    unsigned gt_num_ = 0;
    unsigned gt_dim_ = 0;
    unsigned top_k_ = 0;
};

#endif //GRAPHANNS_EVA_RECALL_NODE_H
