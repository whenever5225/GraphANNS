/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: param_basic_v2.h
@Time: 2022/4/30 17:51
@Desc: 
***************************/

#ifndef GRAPHANNS_BASIC_PARAM_H
#define GRAPHANNS_BASIC_PARAM_H

#include <string>
#include <fstream>

#include "../../utils/utils.h"
#include "params_define.h"
#include "../../../CGraph/src/CGraph.h"
#include "../../graph_anns_define.h"

struct BasicParam : public CGraph::GParam {
    CVoid reset() override {
    }
};

#endif //GRAPHANNS_BASIC_PARAM_H
