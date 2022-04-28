/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: load_for_build.h
@Time: 2022/4/7 8:07 PM
@Desc: load data for index build
***************************/

#ifndef GRAPHANNS_LOAD_FOR_BUILD_H
#define GRAPHANNS_LOAD_FOR_BUILD_H

#include "src/CGraph.h"
#include "../param_nodes/param_include.h"
#include "../../../utils/functions/read_vecs.h"
#include "../config_nodes/config_include.h"

class LoadForBuild : public CGraph::GNode {
public:

    CStatus run() override {

        auto *g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param)

        read_vecs(&g_param->base_path[0], g_param->data, g_param->num, g_param->dim);
        CGraph::CGRAPH_ECHO("vector path: [%s]", g_param->base_path.c_str());
        CGraph::CGRAPH_ECHO("vector num: [%d]", g_param->num);
        CGraph::CGRAPH_ECHO("vector dim: [%d]", g_param->dim);
        return CStatus();
    }
};

#endif //GRAPHANNS_LOAD_FOR_BUILD_H
