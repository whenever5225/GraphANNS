/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: config_model_node.h
@Time: 2022/5/2 11:34
@Desc: 
***************************/

#ifndef GRAPHANNS_CONFIG_MODEL_NODE_H
#define GRAPHANNS_CONFIG_MODEL_NODE_H

#include "../config_basic.h"
#include "../../../elements_define.h"

class ConfigModelNode : public ConfigBasic {
public:
    CStatus init() override {
        return CGRAPH_CREATE_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
    }

    CStatus run() override {
        return CStatus();
    }
};

#endif //GRAPHANNS_CONFIG_MODEL_NODE_H
