/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: load_for_eva.h
@Time: 2022/4/8 4:25 PM
@Desc: load data for performance evaluation
***************************/

#ifndef GRAPHANNS_LOAD_FOR_EVA_H
#define GRAPHANNS_LOAD_FOR_EVA_H

#include "src/CGraph.h"
#include "../param_nodes/param_include.h"
#include "../../../utils/function/read_vecs.h"
#include "../config_nodes/config_include.h"

class LoadForEva : public CGraph::GNode {
public:

    CStatus run() override {
        auto *g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param)

        read_vecs(&g_param->groundtruth_path[0], g_param->gt, g_param->gt_num, g_param->gt_dim);
        return CStatus();
    }
};

#endif //GRAPHANNS_LOAD_FOR_EVA_H
