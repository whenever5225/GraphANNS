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

struct NPGTrainParam : public BasicParam {
    unsigned L_candidate = Params.L_candidate_;    // size of candidate set for neighbor selection
    unsigned R_neighbor = Params.R_neighbor_;      // size of neighbor set
    unsigned C_neighbor = Params.C_neighbor_;      // number of visited candidate neighbors when neighbor selection
    unsigned k_init_graph = Params.k_init_graph_;  // number of neighbors of initial graph
    unsigned nn_size = Params.nn_size_;            // size of candidate neighbors during nn-descent
    unsigned rnn_size = Params.rnn_size_;          // size of reverse candidate neighbors during nn-descent
    unsigned pool_size = Params.pool_size_;        // size of neighbor pool during nn-descent
    unsigned iter = Params.iter_;                  // number of nn-descent iteration
    unsigned sample_num = Params.sample_num_;      // number of sample data when evaluating graph quality for each iteration
    float graph_quality_threshold = Params.graph_quality_threshold_;         // graph quality threshold

    CVoid reset() override {

    }
};

#endif //GRAPHANNS_NPG_TRAIN_PARAM_H
