/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: load_for_search.h
@Time: 2022/4/7 7:53 PM
@Desc: load data for search
***************************/

#ifndef GRAPHANNS_LOAD_FOR_SEARCH_H
#define GRAPHANNS_LOAD_FOR_SEARCH_H

#include "src/CGraph.h"
#include "../param_nodes/param_include.h"
#include "../../../utils/function/read_vecs.h"
#include "../config_nodes/config_include.h"

class LoadForSearch : public CGraph::GNode {
public:
    CStatus run() override {
        auto *g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param)

        read_vecs(&g_param->base_path[0], g_param->data, g_param->num, g_param->dim);
        read_vecs(&g_param->query_path[0], g_param->query, g_param->q_num, g_param->q_dim);

        return CStatus();

    }
};

#endif //GRAPHANNS_LOAD_FOR_SEARCH_H
