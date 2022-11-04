/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: anns_model_param.h
@Time: 2022/5/2 11:01
@Desc: 
***************************/

#ifndef GRAPHANNS_ANNS_MODEL_PARAM_H
#define GRAPHANNS_ANNS_MODEL_PARAM_H

#include "../../../CGraph/src/CGraph.h"
#include "../neighbors/neighbors_include.h"
#include "../meta/meta_include.h"

struct AnnsModelParam : public CGraph::GParam {
    std::vector<Neighbor> pool_;
    std::vector<std::vector<Neighbor> > pool_m_;
    std::vector<std::vector<Neighbor> > cut_graph_;

    IDType cur_id_ = 0;
    typedef std::vector<std::vector<Neighbor> > graph_neighbor;
    typedef std::vector<std::vector<IDType> > graph_matrix;

    graph_neighbor graph_n_;
    graph_matrix graph_m_;
    graph_matrix graph_m1_;
    graph_matrix graph_m2_;

    MetaData<VecValType1> train_meta_modal1_;
    MetaData<VecValType2> train_meta_modal2_;
    MetaData<VecValType1> search_meta_modal1_;
    MetaData<VecValType2> search_meta_modal2_;
    MetaVector<IDType> eva_meta_;
    MetaData<IDType> delete_meta_;

    CVoid reset() override {
           }
};

#endif //GRAPHANNS_ANNS_MODEL_PARAM_H
