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
    unsigned search_L = Params.L_search_;
    unsigned query_id = 0;
    unsigned modal1_query_id = 0;
    unsigned modal2_query_id = 0;

    std::vector<NeighborFlag> sp;
    std::vector<NeighborFlag> sp_modal1;
    std::vector<NeighborFlag> sp_modal2;

    CVoid reset() override {
        sp.clear();
        sp_modal1.clear();
        sp_modal2.clear();
    }
};

#endif //GRAPHANNS_NPG_SEARCH_PARAM_H
