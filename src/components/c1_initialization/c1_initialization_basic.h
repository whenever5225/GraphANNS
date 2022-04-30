/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c1_initialization_basic.h
@Time: 2022/4/11 7:04 PM
@Desc:
***************************/

#ifndef GRAPHANNS_C1_INITIALIZATION_BASIC_H
#define GRAPHANNS_C1_INITIALIZATION_BASIC_H

#include "../components_basic.h"
#include "../../utils/utils.h"

class C1InitializationBasic : public ComponentsBasic {
protected:
    CStatus init() override {
        auto *g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param)

        read_vecs(&g_param->base_path[0], g_param->data, g_param->num, g_param->dim);
        CGraph::CGRAPH_ECHO("vector path: [%s]", g_param->base_path.c_str());
        CGraph::CGRAPH_ECHO("vector num: [%d]", g_param->num);
        CGraph::CGRAPH_ECHO("vector dim: [%d]", g_param->dim);
        return CStatus();
    }

protected:
    unsigned out_degree_ = 0;   // out-degree of initial graph
    unsigned cur_num_ = 0;  // number of the data being processed
};

#endif //GRAPHANNS_C1_INITIALIZATION_BASIC_H
