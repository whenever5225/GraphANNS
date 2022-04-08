/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: eva_recall.h
@Time: 2022/4/8 4:31 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_EVA_RECALL_H
#define GRAPHANNS_EVA_RECALL_H
#include "../../CGraph/src/CGraph.h"
#include "../params/vector_params.h"
#include "../params/search_params.h"

/**
 * calculate recall rate
 */

class EvaRecall : public CGraph::GNode {
public:
    CStatus run() override {
        auto *v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info");
        auto *s_param = CGRAPH_GET_GPARAM(SearchParams, "search_info");
        int cnt = 0;
        for (unsigned i = 0; i < v_param->gt_num; i++) {
            if (s_param->results[i].size() == 0) continue;
            for (unsigned j = 0; j < s_param->top_k; j++) {
                unsigned k = 0;
                for (; k < s_param->top_k; k++) {
                    if (s_param->results[i][j] == v_param->gt[i * v_param->gt_dim + k])
                        break;
                }
                if (k == s_param->top_k)
                    cnt++;
            }
        }

        float acc = 1 - (float) cnt / (float)(v_param->gt_num * s_param->top_k);
        printf("%d NN accuracy: %f", s_param->top_k, acc);
        return CStatus();
    }
};
#endif //GRAPHANNS_EVA_RECALL_H
