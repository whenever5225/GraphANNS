/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: build_region.h
@Time: 2022/4/19 4:31 PM
@Desc: region for index building
***************************/

#ifndef GRAPHANNS_BUILD_REGION_H
#define GRAPHANNS_BUILD_REGION_H

#include "src/CGraph.h"
#include "../nodes/param_nodes/param_include.h"

class BuildRegion : public CGraph::GRegion {
public:
    CBool isHold() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY)
        g_param->cur_id++;
        return g_param->cur_id < g_param->num;
    }
};

#endif //GRAPHANNS_BUILD_REGION_H
