/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: hnsw_show_node.h
@Time: 2022/6/4 01:02
@Desc: 
***************************/

#ifndef GRAPHANNS_HNSW_SHOW_NODE_H
#define GRAPHANNS_HNSW_SHOW_NODE_H

#include "../../../CGraph/src/CGraph.h"

class HnswShowNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto param = CGRAPH_GET_GPARAM(HnswParam, HNSW_PARAM_KEY)

        for (int i = 0; i < param->candidate_.size(); i++) {
            printf("==== [%d] candidate [%d], distance is [%f] ==== \n", i, param->candidate_[i], param->distance_[i]);
        }

        return CStatus();
    }
};

#endif //GRAPHANNS_HNSW_SHOW_NODE_H
