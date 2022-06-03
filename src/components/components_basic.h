/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: component_basic.h
@Time: 2022/4/30 14:40
@Desc: 
***************************/

#ifndef GRAPHANNS_COMPONENTS_BASIC_H
#define GRAPHANNS_COMPONENTS_BASIC_H

#include "../../CGraph/src/CGraph.h"
#include "../utils/utils.h"

class ComponentsBasic : public CGraph::DAnnNode {
protected:
    AnnsModelParam* model_ = nullptr;          // ann model ptr
    VecValType *data_ = nullptr;               // vector data
    unsigned num_ = 0;                         // number of vector
    unsigned dim_ = 0;                         // dimensionality of vector
    DistCalcType dist_op_;                     // distance calc tool
};

#endif //GRAPHANNS_COMPONENTS_BASIC_H
