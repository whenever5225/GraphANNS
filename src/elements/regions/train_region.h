/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: train_region.h
@Time: 2022/4/19 4:31 PM
@Desc: region for index building
***************************/

#ifndef GRAPHANNS_TRAIN_REGION_H
#define GRAPHANNS_TRAIN_REGION_H

#include "src/CGraph.h"
#include "../nodes/params/param_include.h"

class TrainRegion : public CGraph::GRegion {
public:
    CBool isHold() override {
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        t_param->cur_id++;
        return t_param->cur_id < t_param->num;
    }
};

#endif //GRAPHANNS_TRAIN_REGION_H
