/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: distance_naive.h
@Time: 2022/4/1 9:16 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_DISTANCE_NAIVE_H
#define GRAPHANNS_DISTANCE_NAIVE_H

#include "../../CGraph/src/CGraph.h"

/**
 * Euclidean distance calculation
 * @tparam T
 * @tparam needSqrt
 */

template<typename T = CFloat, const CBool needSqrt = false>
class EuclideanDistance : public CGraph::UDistance<T> {
public:
    CStatus calc(const T *a, const T *b, CSize dim1, CSize dim2, T &res, CVoidPtr ext) override {
        if (dim1 != dim2) {
            return CStatus("Euclidean distance requires the same dimension!");
        }
        res = 0;
        float diff0, diff1, diff2, diff3;
        const float *last = a + dim1;
        const float *unroll_group = last - 3;

        while (a < unroll_group) {
            diff0 = a[0] - b[0];
            diff1 = a[1] - b[1];
            diff2 = a[2] - b[2];
            diff3 = a[3] - b[3];
            res += diff0 * diff0 + diff1 * diff1 + diff2 * diff2 + diff3 * diff3;
            a += 4;
            b += 4;
        }

        while (a < last) {
            diff0 = *a++ - *b++;
            res += diff0 * diff0;
        }

        res = needSqrt ? std::sqrt(res) : res;

        return CStatus();
    }
};

#endif //GRAPHANNS_DISTANCE_NAIVE_H
