/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: hnsw_param.h
@Time: 2022/6/4 01:02
@Desc: 
***************************/

#ifndef GRAPHANNS_HNSW_PARAM_H
#define GRAPHANNS_HNSW_PARAM_H

#include <queue>

#include "../../../CGraph/src/CGraph.h"
#include "../../../3rd-anns/hnswlib/hnswlib/hnswalg.h"

#include "../hnsw_define.h"

struct HnswParam : public CGraph::DAnnParam {
    HnswParam() {
        ef_ = HNSW_EF;
        ef_constructor_ = HNSW_EF_CONSTRUCTOR;
        neighbor_size_ = HNSW_NEIGHBOR_SIZE;
        cur_vec_size_ = HNSW_CUR_VEC_SIZE;
        max_vec_size_ = HNSW_MAX_VEC_SIZE;
        dim_ = HNSW_DIM;
        ann_model_path_ = HNSW_MODEL_PATH;
        top_k_ = HNSW_TOP_K;
    }

    unsigned ef_;
    unsigned ef_constructor_;
    unsigned neighbor_size_;
    unsigned top_k_;

    std::vector<unsigned> candidate_;
    std::vector<HNSW_DIST_TYPE> distance_;
    std::vector<HNSW_DIST_TYPE> query_;    // query data info
    std::vector<std::vector<HNSW_DIST_TYPE> > data_;    // mata data info for train annoy model

    CVoid reset() override {
        query_.clear();
        data_.clear();
        candidate_.clear();
        distance_.clear();
    }
};

#endif //GRAPHANNS_HNSW_PARAM_H
