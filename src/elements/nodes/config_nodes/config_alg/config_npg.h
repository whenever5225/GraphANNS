/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: config_npg.h
@Time: 2022/4/14 6:56 PM
@Desc: 'npg' algorithm configuration
***************************/

#ifndef GRAPHANNS_CONFIG_NPG_H
#define GRAPHANNS_CONFIG_NPG_H

#include "../config_basic.h"

class ConfigNPG : public ConfigBasic {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        return status;
    }

    CStatus run() override {
        auto *npg_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(npg_param)
        npg_param->base_path = "/Users/wmz/Documents/Postgraduate/Code/dataset/siftsmall/siftsmall_base.fvecs";
        npg_param->query_path = "/Users/wmz/Documents/Postgraduate/Code/dataset/siftsmall/siftsmall_query.fvecs";
        npg_param->groundtruth_path = "/Users/wmz/Documents/Postgraduate/Code/dataset/siftsmall/siftsmall_groundtruth.ivecs";

        npg_param->index_path = "/Users/wmz/Documents/Postgraduate/Code/tmp/test.index";

        npg_param->L_candidate = 100;
        npg_param->R_neighbor = 100;
        npg_param->C_neighbor = 200;
        npg_param->k_init_graph = 20;
        return CStatus();
    }
};

#endif //GRAPHANNS_CONFIG_NPG_H
