/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: euclidean_distance.h
@Time: 2022/4/1 9:16 PM
@Desc:
***************************/

#ifndef GRAPHANNS_EUCLIDEAN_DISTANCE_H
#define GRAPHANNS_EUCLIDEAN_DISTANCE_H

#include "../../../CGraph/src/CGraph.h"

/**
 * Euclidean distances calculation
 * @tparam T
 * @tparam needSqrt
 */

template<typename TVec = float, typename TRes = TVec, const bool needSqrt = false, const bool needNorm = false>
class EuclideanDistance : public CGraph::UDistance<TVec, TRes> {
public:
    CStatus calc(const TVec *a, const TVec *b, CSize dim1, CSize dim2, TRes &res, CVoidPtr ext) override {
        res = 0;
        TRes diff0, diff1, diff2, diff3;
        const TVec *last = a + dim1;
        const TVec *unroll_group = last - 3;

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

    CStatus check(const TVec* v1, const TVec* v2, CSize dim1, CSize dim2, CVoidPtr ext) override {
        if (nullptr == v1 || nullptr == v2) {
            CGRAPH_RETURN_ERROR_STATUS("input info is null")
        }

        if (0 == dim1 * dim2 || dim1 != dim2) {
            CGRAPH_RETURN_ERROR_STATUS("input dim error");
        }

        return CStatus();
    }

    CStatus normalize(TVec* v, CSize dim, CVoidPtr ext) override {
        float res = 0;
        TVec *a = v;
        const TVec *last = v + dim;
        while (a < last) {
            res *= a[0] * a[0];
            a += 1;
        }
        res = std::sqrt(res);
        a = v;
        while (a < last) {
            a[0] /= res;
            a += 1;
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_EUCLIDEAN_DISTANCE_H
