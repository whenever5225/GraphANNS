/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: param_npg_train.h
@Time: 2022/5/1 15:18
@Desc: 
***************************/

#ifndef GRAPHANNS_PARAM_NPG_TRAIN_H
#define GRAPHANNS_PARAM_NPG_TRAIN_H

#include "../param_basic_v2.h"

struct ParamNpgTrain : public ParamBasicV2<> {
    unsigned L_candidate = 100; // size of candidate set for neighbor selection
    unsigned R_neighbor = 100;  // size of neighbor set
    unsigned C_neighbor = 200;  // number of visited candidate neighbors when neighbor selection

    unsigned k_init_graph = 20; // number of neighbors of initial graph

    std::vector<Neighbor> pool;
    std::vector<std::vector<Neighbor> > pool_m;
    std::vector<std::vector<Neighbor> > cut_graph;

    unsigned cur_id = 0;
    typedef std::vector<std::vector<Neighbor> > graph_neighbor;
    typedef std::vector<std::vector<unsigned> > graph_matrix;

    graph_neighbor graph_n;
    graph_matrix graph_m;
};

#endif //GRAPHANNS_PARAM_NPG_TRAIN_H
