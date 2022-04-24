/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: utils_proxy.h
@Time: 2022/4/11 8:32 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_UTILS_PROXY_H
#define GRAPHANNS_UTILS_PROXY_H

#include "../CGraph/src/CGraph.h"
#include "../elements/distances/euclidean_distance.h"

using VecValType = float;   // vector value type
using DistResType = float;  // distances value type

// distances calculation method
CGraph::UDistanceCalculator<VecValType, DistResType, EuclideanDistance<VecValType, DistResType> > eucDist;

#endif //GRAPHANNS_UTILS_PROXY_H
