/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: annoy_prepare_node.h
@Time: 2022/5/24 00:22
@Desc: 
***************************/

#ifndef GRAPHANNS_ANNOY_PREPARE_NODE_H
#define GRAPHANNS_ANNOY_PREPARE_NODE_H

#include "../../../CGraph/src/CGraph.h"

#include "../param/annoy_param.h"

class AnnoyPrepareNode : public CGraph::GNode {
public:
    CStatus run() override {
        CGraph::CGRAPH_ECHO("AnnoyPrepareNode start ... ");
        auto param = CGRAPH_GET_GPARAM(AnnoyParam, ANNOY_PARAM_KEY);
        if (nullptr == param) {
            CGRAPH_RETURN_ERROR_STATUS("AnnoyPrepareNode run input is nullptr")
        }

        if (ANNOY_FUNC_TYPE == DAnnFuncType::ANN_TRAIN) {
            /** build random data when train */
            CGraph::URandom<ANNOY_DIST_TYPE, ANNOY_BUILD_RANDOM_SEED>::generate(param->data_, param->max_vec_size_, param->dim_, ANNOY_MIN_VALUE, ANNOY_MAX_VALUE);
        } else if (ANNOY_FUNC_TYPE == DAnnFuncType::ANN_SEARCH) {
            /** build a random node for query */
            CGraph::URandom<ANNOY_DIST_TYPE, ANNOY_QUERY_RANDOM_SEED>::generate(param->query_, param->dim_, ANNOY_MIN_VALUE, ANNOY_MAX_VALUE);
        }

        CGraph::CGRAPH_ECHO("AnnoyPrepareNode finish ... ");
        return CStatus();
    }
};

#endif //GRAPHANNS_ANNOY_PREPARE_NODE_H
