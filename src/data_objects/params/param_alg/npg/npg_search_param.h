/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: param_npg_search.h
@Time: 2022/5/1 15:25
@Desc: 
***************************/

#ifndef GRAPHANNS_NPG_SEARCH_PARAM_H
#define GRAPHANNS_NPG_SEARCH_PARAM_H

#include "../../basic_param.h"

struct NPGSearchParam : public BasicParam<> {
    unsigned top_k = 20;
    unsigned search_L = top_k + 500;
    unsigned query_id = 0;

    std::vector<NeighborFlag> sp;
    std::vector<std::vector<IDType> > results;

    CVoid reset() override {
        sp.clear();
    }
};

#endif //GRAPHANNS_NPG_SEARCH_PARAM_H
