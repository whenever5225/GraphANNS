/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: utils_define.h
@Time: 2022/4/11 8:32 PM
@Desc:
***************************/

#ifndef GRAPHANNS_UTILS_DEFINE_H
#define GRAPHANNS_UTILS_DEFINE_H

#include "../CGraph/src/CGraph.h"
#include "distances/distances_include.h"

using VecValType = float;   // vector value type
using DistResType = float;  // distances value type

// distances calculation type
using DistCalcType = CGraph::UDistanceCalculator<VecValType, DistResType, EuclideanDistance<VecValType, DistResType> >;

#endif //GRAPHANNS_UTILS_DEFINE_H
