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
        status += CGRAPH_CREATE_GPARAM(AlgParamBasic, GA_ALG_PARAM_BASIC_KEY)
        return status;
    }

    CStatus run() override {
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(t_param)

        t_param->L_candidate = Params.L_candidate_;
        t_param->R_neighbor = Params.R_neighbor_;
        t_param->C_neighbor = Params.C_neighbor_;
        t_param->k_init_graph = Params.k_init_graph_;

        return CStatus();
    }
};

#endif //GRAPHANNS_CONFIG_ALG_NPG_NODE_H
