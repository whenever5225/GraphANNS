/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: hnsw_define.h
@Time: 2022/6/4 01:02
@Desc: 
***************************/

#ifndef GRAPHANNS_HNSW_DEFINE_H
#define GRAPHANNS_HNSW_DEFINE_H

#include "../3rd_anns_define.h"

using HNSW_DIST_TYPE = ANNS_DIST_TYPE;

static constexpr HNSW_DIST_TYPE HNSW_MIN_VALUE = ANNS_MIN_VALUE;    // min data value
static constexpr HNSW_DIST_TYPE HNSW_MAX_VALUE = ANNS_MAX_VALUE;    // max data value
static constexpr int HNSW_BUILD_RANDOM_SEED = ANNS_BUILD_RANDOM_SEED;    // build random seed
static constexpr int HNSW_QUERY_RANDOM_SEED = ANNS_QUERY_RANDOM_SEED;    // query random seed, 0 is for real random

static constexpr unsigned HNSW_CUR_VEC_SIZE = ANNS_CUR_VEC_SIZE;
static constexpr unsigned HNSW_MAX_VEC_SIZE = ANNS_MAX_VEC_SIZE;    // total data size, as same as HNSW_CUR_VEC_SIZE
static constexpr unsigned HNSW_DIM = ANNS_DIM;    // vec dim
static constexpr unsigned HNSW_TOP_K = ANNS_TOP_K;    // top k

static DAnnFuncType HNSW_FUNC_TYPE = DAnnFuncType::ANN_PREPARE_ERROR;
static const char* HNSW_MODEL_PATH = "hnsw.model";    // model file path
static const char* HNSW_PARAM_KEY = "hnsw-param";    // param key

/**
 * hnsw own param
 */
static const unsigned HNSW_EF = 64;    // the size of the dynamic list for the nearest neighbors (used during the search)
static const unsigned HNSW_EF_CONSTRUCTOR = 64;    // the parameter has the same meaning as ef, but controls the index_time/index_accuracy
static const unsigned HNSW_NEIGHBOR_SIZE = 32;    // the number of bi-directional links created for every new element during construction

#endif //GRAPHANNS_HNSW_DEFINE_H
