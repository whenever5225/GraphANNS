/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c2_candidate_basic.h
@Time: 2022/4/18 11:41 AM
@Desc:
***************************/

#ifndef GRAPHANNS_C2_CANDIDATE_BASIC_H
#define GRAPHANNS_C2_CANDIDATE_BASIC_H

#include "../components_basic.h"
#include "../../utils/utils.h"

class C2CandidateBasic : public ComponentsBasic {
protected:
    IDType cur_id_ = 0;  // data id being processed
    unsigned L_ = 0;
};

#endif //GRAPHANNS_C2_CANDIDATE_BASIC_H
