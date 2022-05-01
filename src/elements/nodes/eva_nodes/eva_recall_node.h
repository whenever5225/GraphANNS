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
#include "../params/param_include.h"

class EvaRecallNode : public CGraph::GNode {
public:
    CStatus init() override {
        /**
         * todo eval 这个节点，需要重写一下
         * 一起看一下吧
         */
        auto *g_param = CGRAPH_GET_GPARAM(EvaParam, GA_ALG_NPG_EVA_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param)
        CStatus status = g_param->load(GA_ALG_GROUNDTRUTH_PATH);
        return status;
    }

    CStatus run() override {
//        auto *g_param = CGRAPH_GET_GPARAM(EvaParam, GA_ALG_NPG_EVA_PARAM_KEY);
//        gt_num_ = g_param->gt_num;
//        gt_dim_ = g_param->gt_dim;
//        top_k_ = g_param->top_k;
//        int cnt = 0;
//        for (unsigned i = 0; i < gt_num_; i++) {
//            if (g_param->results[i].empty()) continue;
//            for (unsigned j = 0; j < top_k_; j++) {
//                unsigned k = 0;
//                for (; k < top_k_; k++) {
//                    if (g_param->results[i][j] == g_param->gt[i * gt_dim_ + k])
//                        break;
//                }
//                if (k == top_k_)
//                    cnt++;
//            }
//        }
//
//        float acc = 1 - (float) cnt / (float) (gt_num_ * top_k_);
//        CGraph::CGRAPH_ECHO("%d NN accuracy: %f", top_k_, acc);
        return CStatus();
    }

    CStatus destroy() override {
        return CStatus();
    }

private:
    unsigned gt_num_ = 0;
    unsigned gt_dim_ = 0;
    unsigned top_k_ = 0;

};

#endif //GRAPHANNS_EVA_RECALL_NODE_H
