/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: annoy_param.h
@Time: 2022/5/21 15:11
@Desc: 
***************************/

#ifndef GRAPHANNS_ANNOY_PARAM_H
#define GRAPHANNS_ANNOY_PARAM_H

#include "src/CGraph.h"

#include "../annoy_define.h"

struct AnnoyParam : public CGraph::DAnnParam {
    AnnoyParam() {
        dim_ = ANNOY_DIM;
        ann_model_path_ = ANNOY_MODEL_PATH;
        max_vec_size_ = ANNOY_MAX_VEC_SIZE;

        tree_size_ = ANNOY_TREE_SIZE;
        search_k_ = ANNOY_SEARCH_K;
        build_thread_num_ = ANNOY_BUILD_THREAD_NUM;
    }

    CVoid reset() override {
        candidate_.clear();
        distance_.clear();
        data_.clear();
        query_.clear();
    }

    int tree_size_;
    int search_k_;
    int build_thread_num_;

    std::vector<int> candidate_;
    std::vector<ANNOY_DIST_TYPE> distance_;

    std::vector<ANNOY_DIST_TYPE> query_;    // query data info
    std::vector<std::vector<ANNOY_DIST_TYPE> > data_;    // mata data info for train annoy model
};

#endif //GRAPHANNS_ANNOY_PARAM_H
