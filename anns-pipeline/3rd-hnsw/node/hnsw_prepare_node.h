/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: hnsw_prepare_node.h
@Time: 2022/6/4 01:01
@Desc: 
***************************/

#ifndef GRAPHANNS_HNSW_PREPARE_NODE_H
#define GRAPHANNS_HNSW_PREPARE_NODE_H

#include "../../../CGraph/src/CGraph.h"

#include "../param/hnsw_param.h"
#include "../hnsw_define.h"

class HnswPrepareNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto param = CGRAPH_GET_GPARAM(HnswParam, HNSW_PARAM_KEY);
        if (nullptr == param) {
            CGRAPH_RETURN_ERROR_STATUS("HnswPrepareNode run input is nullptr")
        }

        if (HNSW_FUNC_TYPE == DAnnFuncType::ANN_TRAIN) {
            /** build random data when train */
            CGraph::URandom<HNSW_DIST_TYPE, HNSW_BUILD_RANDOM_SEED>::generate(param->data_, param->cur_vec_size_, param->dim_, HNSW_MIN_VALUE, HNSW_MAX_VALUE);
        } else if (HNSW_FUNC_TYPE == DAnnFuncType::ANN_SEARCH) {
            /** build a random node for query */
            CGraph::URandom<HNSW_DIST_TYPE, HNSW_QUERY_RANDOM_SEED>::generate(param->query_, param->dim_, HNSW_MIN_VALUE, HNSW_MAX_VALUE);
        }

        return CStatus();
    }
};

#endif //GRAPHANNS_HNSW_PREPARE_NODE_H
