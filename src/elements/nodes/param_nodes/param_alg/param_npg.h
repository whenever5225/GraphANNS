/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: param_npg.h
@Time: 2022/4/4 8:55 PM
@Desc: parameters for our graph-based ANNS algorithm 'npg'
***************************/

#ifndef GRAPHANNS_NPG_PARAMS_H
#define GRAPHANNS_NPG_PARAMS_H

#include "../param_basic.h"

static const char* GRAPH_INFO_PARAM_KEY = "NPG_info";

class ParamNPG : public ParamBasic {
public:
    unsigned L_candidate = 100; // size of candidate set for neighbor selection
    unsigned R_neighbor = 100;  // size of neighbor set
    unsigned C_neighbor = 200;  // number of visited candidate neighbors when neighbor selection

    unsigned k_init_graph = 20; // number of neighbors of initial graph

    std::vector<Neighbor> pool;
    std::vector<std::vector<Neighbor> > pool_m;
    std::vector<std::vector<Neighbor> > cut_graph;

    CVoid reset() override {

    }
};

#endif //GRAPHANNS_NPG_PARAMS_H
