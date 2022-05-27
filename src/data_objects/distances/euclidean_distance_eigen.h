/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: euclidean_distance_eigen.h
@Time: 2022/5/26 22:48
@Desc: 
***************************/

#ifndef GRAPHANNS_EUCLIDEAN_DISTANCE_EIGEN_H
#define GRAPHANNS_EUCLIDEAN_DISTANCE_EIGEN_H

#include "euclidean_distance.h"

#if GA_USE_EIGEN3

#include <Eigen/Core>

template<typename TVec = float, typename TRes = TVec, const bool needSqrt = false>
class EuclideanDistanceEigen : public EuclideanDistance<TVec, TRes, needSqrt> {
    using EigenDynamicMatrix = Eigen::Map<Eigen::Matrix<TVec, 1, Eigen::Dynamic> >;

public:
    CStatus calc(const TVec *a, const TVec *b, CSize dim1, CSize dim2, TRes &res, CVoidPtr ext) override {
        EigenDynamicMatrix v1((TVec *)a, dim1);
        EigenDynamicMatrix v2((TVec *)b, dim2);

        res = static_cast<TRes>(needSqrt ? (v1-v2).norm() : (v1-v2).squaredNorm());    // calc euclidean distance with sqrt
        return CStatus();
    }
};

#else

/** degrade to basic version if input eigen failed */
template<typename TVec = float, typename TRes = TVec, const bool needSqrt = false>
using EuclideanDistanceEigen = EuclideanDistance<TVec, TRes, needSqrt>;

#endif

#endif //GRAPHANNS_EUCLIDEAN_DISTANCE_EIGEN_H
