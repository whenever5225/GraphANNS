/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c6_seed_basic.h
@Time: 2022/4/21 10:10 AM
@Desc:
***************************/

#ifndef GRAPHANNS_C6_SEED_BASIC_H
#define GRAPHANNS_C6_SEED_BASIC_H

#include "../../CGraph/src/CGraph.h"
#include "../../utils/utils.h"
#include "../../elements/elements.h"

class C6SeedBasic : public CGraph::DAnnNode {
protected:
    unsigned num_;  // number of vector
    unsigned dim_;  // dimensionality of vector
    unsigned search_L_; // candidate pool size for search
};

#endif //GRAPHANNS_C6_SEED_BASIC_H
