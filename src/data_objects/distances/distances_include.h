/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: distances_include.h
@Time: 2022/4/12 2:28 PM
@Desc:
***************************/

#ifndef GRAPHANNS_DISTANCES_INCLUDE_H
#define GRAPHANNS_DISTANCES_INCLUDE_H

#include "euclidean_distance.h"
#include "euclidean_distance_eigen.h"

using VecValType = float;   // vector value type
using DistResType = float;  // distances value type

// distances calculation type
using DistCalcType = CGraph::UDistanceCalculator<VecValType, DistResType, EuclideanDistance<VecValType, DistResType> >;

#endif //GRAPHANNS_DISTANCES_INCLUDE_H
