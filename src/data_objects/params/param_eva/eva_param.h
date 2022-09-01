/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: eva_param.h
@Time: 2022/4/8 4:36 PM
@Desc: parameters for performance evaluation
***************************/

#ifndef GRAPHANNS_EVA_PARAM_H
#define GRAPHANNS_EVA_PARAM_H

#include "../../../../CGraph/src/CGraph.h"
#include "../basic_param.h"

struct EvaParam : public BasicParam {
    CVoid reset() override {
    }
};

#endif //GRAPHANNS_EVA_PARAM_H
