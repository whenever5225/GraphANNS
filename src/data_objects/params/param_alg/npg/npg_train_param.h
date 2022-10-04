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
    unsigned k_init_graph = 100;     // number of neighbors of initial graph
    unsigned nn_size = 50;        // size of candidate neighbors during nn-descent
    unsigned rnn_size = 25;        // size of reverse candidate neighbors during nn-descent
    unsigned pool_size = 200;        // size of neighbor pool during nn-descent
    unsigned iter = 5;        // number of nn-descent iteration
    unsigned sample_num = 100;        // number of sample data when evaluating graph quality for each iteration
    float graph_quality_threshold = 0.8;         // graph quality threshold
};

#endif //GRAPHANNS_NPG_TRAIN_PARAM_H
