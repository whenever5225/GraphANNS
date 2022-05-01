/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c3_neighbor_basic.h
@Time: 2022/4/19 4:23 PM
@Desc:
***************************/

#ifndef GRAPHANNS_C3_NEIGHBOR_BASIC_H
#define GRAPHANNS_C3_NEIGHBOR_BASIC_H

#include "../components_basic.h"
#include "../../elements/nodes/params/param_include.h"
#include "../../utils/utils.h"

class C3NeighborBasic : public ComponentsBasic {
protected:
    unsigned cur_id_ = 0;  // data id being processed
    unsigned C_ = 0;
    unsigned R_ = 0;
    std::vector<Neighbor> result_;
};

#endif //GRAPHANNS_C3_NEIGHBOR_BASIC_H
