/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: attribute_distance.h
@Time: 2022/10/17 9:41 PM
@Desc: attribute distance, number of unequal attributes
***************************/

#ifndef GRAPHANNS_ATTRIBUTE_DISTANCE_H
#define GRAPHANNS_ATTRIBUTE_DISTANCE_H

#include "../../../CGraph/src/CGraph.h"

template<typename TVec = int, typename TRes = TVec, const bool needSqrt = false, const bool needSkip = true>
class AttributeDistance : public CGraph::UDistance<TVec, TRes> {
public:
    CStatus calc(const TVec *a, const TVec *b, CSize dim1, CSize dim2, TRes &res, CVoidPtr ext) override {
        res = 0;
        TRes diff0, diff1, diff2, diff3;
        const TVec *last = a + dim1;
        const TVec *unroll_group = last - 3;

        while (a < unroll_group) {
            diff0 = (a[0] == b[0] ? 0 : 1);
            diff1 = (a[1] == b[1] ? 0 : 1);
            diff2 = (a[2] == b[2] ? 0 : 1);
            diff3 = (a[3] == b[3] ? 0 : 1);
            res += diff0 + diff1 + diff2 + diff3;
            a += 4;
            b += 4;
        }

        while (a < last) {
            diff0 = (*a++ == *b++ ? 0 : 1);
            res += diff0;
        }

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
};

#endif //GRAPHANNS_ATTRIBUTE_DISTANCE_H
