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
    std::vector<Neighbor> pool_;
    std::vector<std::vector<Neighbor> > pool_m_;
    std::vector<std::vector<Neighbor> > cut_graph_;

    unsigned cur_id_ = 0;
    typedef std::vector<std::vector<Neighbor> > graph_neighbor;
    typedef std::vector<std::vector<unsigned> > graph_matrix;

    graph_neighbor graph_n_;
    graph_matrix graph_m_;

    MetaData<VecValType> train_meta_;
    MetaData<VecValType> search_meta_;
    MetaData<unsigned> eva_meta_;

    CVoid reset() override {
        return;
    }
};

#endif //GRAPHANNS_ANNS_MODEL_PARAM_H
