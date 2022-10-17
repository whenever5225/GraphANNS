/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: config_basic.h
@Time: 2022/4/14 6:19 PM
@Desc:
***************************/

#ifndef GRAPHANNS_CONFIG_BASIC_H
#define GRAPHANNS_CONFIG_BASIC_H

#include "../../../../CGraph/src/CGraph.h"
#include "../../../graph_anns_define.h"

class ConfigBasic : public CGraph::GNode {
public:
    CStatus init() override {
        /**
         * load search param
         */
        CStatus status = CGRAPH_CREATE_GPARAM(AlgParamBasic, GA_ALG_PARAM_BASIC_KEY)
        return status;
    }
    CStatus run() override {
        CGRAPH_EMPTY_FUNCTION
    }

};

#endif //GRAPHANNS_CONFIG_BASIC_H
