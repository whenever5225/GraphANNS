/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: annoy_show_node.h
@Time: 2022/5/21 19:01
@Desc: 
***************************/

#ifndef GRAPHANNS_ANNOY_SHOW_NODE_H
#define GRAPHANNS_ANNOY_SHOW_NODE_H

#include "../CGraph/src/CGraph.h"

#include "annoy_param.h"

class AnnoyShowNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto param = CGRAPH_GET_GPARAM(AnnoyParam, ANNOY_PARAM_KEY);
        if (nullptr == param) {
            CGRAPH_RETURN_ERROR_STATUS("AnnoyShowNode run AnnoyParam is null")
        }

        for (int i = 0; i < param->candidate_.size(); i++) {
            printf("==== [%d] candidate [%d], distance is [%f] ==== \n", i, param->candidate_[i], param->distance_[i]);
        }

        return CStatus();
    }
};

#endif //GRAPHANNS_ANNOY_SHOW_NODE_H
