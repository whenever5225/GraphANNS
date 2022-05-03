/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c3_neighbor_basic.h
@Time: 2022/4/19 4:23 PM
@Desc:
***************************/

#ifndef GRAPHANNS_C3_NEIGHBOR_BASIC_H
#define GRAPHANNS_C3_NEIGHBOR_BASIC_H

#include <cmath>

#include "../components_basic.h"
#include "../../utils/utils.h"

class C3NeighborBasic : public ComponentsBasic {
protected:
    unsigned cur_id_ = 0;  // data id being processed
    unsigned C_ = 0;
    unsigned R_ = 0;
    std::vector<Neighbor> result_;

protected:
    /**
     * todo i am not sure weather this function only need in c3
     * if c2 and c3 both need this function, please move it into /utils/function/xxx
     * and then, u may need pass `dist_op_` as a function param,
     * just like `const DistCalcType& calc_op`;
     *
     * @desc check weather q in v1 & v2 lune area.
     * return true(represent q in lune area) if q is real in, and calc function work fine
     */
    CBool inLuneArea(VecValType *q, VecValType *v1, VecValType *v2,
                     CSize dim, DistResType ratio = 1.0,
                     CVoidPtr ext = nullptr) {
        DistResType orig = 0, dist1 = 0, dist2 = 0;
        CStatus status = dist_op_.calculate(v1, q, dim, dim, dist1, ext);
        status += dist_op_.calculate(v2, q, dim, dim, dist2, ext);
        status += dist_op_.calculate(v1, v2, dim, dim, orig, ext);
        return (orig * ratio > std::max(dist1, dist2)) && (status.isOK());
    }
};

#endif //GRAPHANNS_C3_NEIGHBOR_BASIC_H
