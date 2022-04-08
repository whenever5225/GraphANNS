/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: load_for_search.h
@Time: 2022/4/7 7:53 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_LOAD_FOR_SEARCH_H
#define GRAPHANNS_LOAD_FOR_SEARCH_H

#include "../../CGraph/src/CGraph.h"
#include "../params/vector_params.h"
#include "read_vecs.h"

/**
 * load data for search
 */

class LoadForSearch : public CGraph::GNode {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(vector_params, "vector_info");
        return status;
    }

    CStatus run() override {
        auto *v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info");
        v_param->base_path = "/Users/wmz/Documents/Postgraduate/Code/dataset/siftsmall/siftsmall_base.fvecs";
        v_param->query_path = "/Users/wmz/Documents/Postgraduate/Code/dataset/siftsmall/siftsmall_query.fvecs";

        read_vecs(&v_param->base_path[0], v_param->data, v_param->num, v_param->dim);
        read_vecs(&v_param->query_path[0], v_param->query, v_param->q_num, v_param->q_dim);

        return CStatus();

    }
};

#endif //GRAPHANNS_LOAD_FOR_SEARCH_H
