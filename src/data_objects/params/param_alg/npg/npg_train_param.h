/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: npg_train_param.h
@Time: 2022/5/1 15:18
@Desc: 
***************************/

#ifndef GRAPHANNS_NPG_TRAIN_PARAM_H
#define GRAPHANNS_NPG_TRAIN_PARAM_H

#include "../../basic_param.h"

struct NPGTrainParam : public BasicParam<> {
    unsigned L_candidate = 100;     // size of candidate set for neighbor selection
    unsigned R_neighbor = 100;      // size of neighbor set
    unsigned C_neighbor = 200;      // number of visited candidate neighbors when neighbor selection
    unsigned k_init_graph = 20;     // number of neighbors of initial graph
};

#endif //GRAPHANNS_NPG_TRAIN_PARAM_H
