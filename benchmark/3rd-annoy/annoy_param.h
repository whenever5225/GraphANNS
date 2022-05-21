/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: annoy_param.h
@Time: 2022/5/21 15:11
@Desc: 
***************************/

#ifndef GRAPHANNS_ANNOY_PARAM_H
#define GRAPHANNS_ANNOY_PARAM_H

#include "../CGraph/src/CGraph.h"

#include "annoy_define.h"

struct AnnoyParam : public CGraph::DAnnParam {
    AnnoyParam() {
        dim_ = ANNOY_DIM;
        ann_model_path_ = ANNOY_MODEL_PATH;
        max_vec_size_ = ANNOY_MAX_VEC_SIZE;
        tree_size_ = ANNOY_TREE_SIZE;
        search_k_ = ANNOY_SEARCH_K;
    }

    CVoid reset() override {
        candidate_.clear();
        distance_.clear();
    }

    int tree_size_;
    int search_k_;

    std::vector<int> candidate_;
    std::vector<ANNOY_DIST_TYPE> distance_;
};

#endif //GRAPHANNS_ANNOY_PARAM_H
