/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: config_alg_npg_node.h
@Time: 2022/4/14 6:56 PM
@Desc: 'npg' algorithm configuration
***************************/

#ifndef GRAPHANNS_CONFIG_ALG_NPG_NODE_H
#define GRAPHANNS_CONFIG_ALG_NPG_NODE_H

#include "../config_basic.h"
#include "../../../../data_objects/data_objects.h"

class ConfigAlgNPGNode : public ConfigBasic {
public:
    CStatus init() override {
        /**
         * load search & train param
         */
        CStatus status = CGRAPH_CREATE_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        status += CGRAPH_CREATE_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY)
        return status;
    }

    CStatus run() override {
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(t_param)

        t_param->L_candidate = GA_NPG_L_CANDIDATE;
        t_param->R_neighbor = GA_NPG_R_NEIGHBOR;
        t_param->C_neighbor = GA_NPG_C_NEIGHBOR;
        t_param->k_init_graph = GA_NPG_K_INIT_GRAPH;
        return CStatus();
    }
};

#endif //GRAPHANNS_CONFIG_ALG_NPG_NODE_H
