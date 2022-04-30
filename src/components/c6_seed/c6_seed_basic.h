/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c6_seed_basic.h
@Time: 2022/4/21 10:10 AM
@Desc:
***************************/

#ifndef GRAPHANNS_C6_SEED_BASIC_H
#define GRAPHANNS_C6_SEED_BASIC_H

#include "../components_basic.h"
#include "../../utils/utils.h"
#include "../../elements/elements.h"

class C6SeedBasic : public ComponentsBasic {
protected:
    unsigned search_L_; // candidate pool size for search
};

#endif //GRAPHANNS_C6_SEED_BASIC_H
