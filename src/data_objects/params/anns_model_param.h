/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: anns_model_param.h
@Time: 2022/5/2 11:01
@Desc: 
***************************/

#ifndef GRAPHANNS_ANNS_MODEL_PARAM_H
#define GRAPHANNS_ANNS_MODEL_PARAM_H

#include "../../../../CGraph/src/CGraph.h"
#include "../neighbors/neighbors_include.h"
#include "../meta/meta_include.h"

struct AnnsModelParam : public CGraph::GParam {
    std::vector<Neighbor> pool;
    std::vector<std::vector<Neighbor> > pool_m;
    std::vector<std::vector<Neighbor> > cut_graph;

    unsigned cur_id = 0;
    typedef std::vector<std::vector<Neighbor> > graph_neighbor;
    typedef std::vector<std::vector<unsigned> > graph_matrix;

    graph_neighbor graph_n;
    graph_matrix graph_m;

    MetaData<VecValType> train_data;
    MetaData<VecValType> search_data;
    MetaData<unsigned> eva_data;

    CVoid reset() override {
        return;
    }
};

#endif //GRAPHANNS_ANNS_MODEL_PARAM_H
