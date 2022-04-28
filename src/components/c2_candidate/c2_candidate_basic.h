/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c2_candidate_basic.h
@Time: 2022/4/18 11:41 AM
@Desc:
***************************/

#ifndef GRAPHANNS_C2_CANDIDATE_BASIC_H
#define GRAPHANNS_C2_CANDIDATE_BASIC_H

#include "../../CGraph/src/CGraph.h"
#include "../../utils/utils.h"
#include "../../elements/nodes/param_nodes/param_include.h"

class C2CandidateBasic : public CGraph::DAnnNode {
protected:
    unsigned num_ = 0;  // number of vector
    unsigned dim_ = 0;  // dimensionality of vector
    VecValType *data_ = nullptr;   // vector data
    unsigned cur_id_ = 0;  // data id being processed
    unsigned L_ = 0;
};

#endif //GRAPHANNS_C2_CANDIDATE_BASIC_H
