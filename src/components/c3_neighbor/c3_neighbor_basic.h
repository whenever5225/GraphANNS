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
    IDType cur_id_ = 0;  // data id being processed
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
                     CSize dim, DistResType ratio = 1.0, CVoidPtr ext = nullptr) {
        DistResType orig = 0, dist1 = 0, dist2 = 0;
        CStatus status = dist_op_.calculate(v1, q, dim, dim, dist1, ext);
        status += dist_op_.calculate(v2, q, dim, dim, dist2, ext);
        status += dist_op_.calculate(v1, v2, dim, dim, orig, ext);
        return (orig * ratio > std::max(dist1, dist2)) && (status.isOK());
    }

    /**
     * 给 𝑝 选边时，为它的 𝐾 近邻列表 𝐿 中的每个点都设置一个计数器。
     * 比如，对于点对 𝑢 和 𝑣，如果 𝑣 到 𝑢 的距离小于 𝑣 到 𝑝 的距离，则 𝑣 的计数器加一，对 𝐿 中的任意两个点都执行上述操作。
     * 之后，保留 𝑘 个计数器的值最小的点作为 𝑝 的邻居。（计数这一步，不在这里做）
     * 原文链接：https://whenever5225.github.io/2020/05/17/anns-dpg/
     * todo 我感觉这里用p、v、u有点不太好理解，后面可以想想咋改个函数名字，或者描述的明确一点。我朋友约我吃饭捏，哈哈哈哈
     * 但是，抽象出来一个方法，总是没错的
     *
     * 还有，就是我看这个ratio，貌似uv之间的距离应该是不用*ratio的，应该只用pv*ratio，你再确认一下哈
     * @return
     */
    CBool isPointVCountAdd1(VecValType *p, VecValType *u, VecValType *v,
                            CSize dim, DistResType ratio = 1.0, CVoidPtr ext = nullptr) {
        DistResType d_pv = 0, d_uv = 0;
        CStatus status = dist_op_.calculate(p, v, dim, dim, d_pv, ext);
        status += dist_op_.calculate(u, v, dim, dim, d_uv, ext);
        return (d_uv > d_pv * ratio) && (status.isOK());
    }
};

#endif //GRAPHANNS_C3_NEIGHBOR_BASIC_H
