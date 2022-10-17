/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: param_npg_search.h
@Time: 2022/5/1 15:25
@Desc: 
***************************/

#ifndef GRAPHANNS_NPG_SEARCH_PARAM_H
#define GRAPHANNS_NPG_SEARCH_PARAM_H

#include "../alg_param_basic.h"

struct NPGSearchParam : public BasicParam {
    unsigned search_L = 10;
    unsigned query_id = 0;

    std::vector<NeighborFlag> sp;

    CVoid reset() override {
        sp.clear();
    }
};

#endif //GRAPHANNS_NPG_SEARCH_PARAM_H
