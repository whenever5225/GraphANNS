/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: npg_params.h
@Time: 2022/4/4 8:55 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_NPG_PARAMS_H
#define GRAPHANNS_NPG_PARAMS_H
#include "../../CGraph/src/CGraph.h"
#include "../graph_params.h"

/**
 * parameters for our graph-based ANNS algorithm 'npg'
 */

class npg_params : public CGraph::GParam{
public:
    unsigned L_candidate = 100;
    unsigned R_neighbor = 100;
    unsigned C_neighbor = 200;


    std::vector<std::vector<graph_params::simple_neighbor> > pool;
    std::vector<std::vector<graph_params::simple_neighbor> > cut_graph;

    CVoid reset()override{

    }
};
#endif //GRAPHANNS_NPG_PARAMS_H
