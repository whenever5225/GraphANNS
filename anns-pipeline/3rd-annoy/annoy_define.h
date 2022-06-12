/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: annoy_define.h
@Time: 2022/5/21 15:58
@Desc: 
***************************/

#ifndef GRAPHANNS_ANNOY_DEFINE_H
#define GRAPHANNS_ANNOY_DEFINE_H

#include "../3rd_anns_define.h"

using ANNOY_DIST_TYPE = ANNS_DIST_TYPE;

static constexpr ANNOY_DIST_TYPE ANNOY_MIN_VALUE = ANNS_MIN_VALUE;    // min data value
static constexpr ANNOY_DIST_TYPE ANNOY_MAX_VALUE = ANNS_MAX_VALUE;    // max data value
static constexpr int ANNOY_BUILD_RANDOM_SEED = ANNS_BUILD_RANDOM_SEED;    // build random seed
static constexpr int ANNOY_QUERY_RANDOM_SEED = ANNS_QUERY_RANDOM_SEED;    // query random seed, 0 is for real random

static constexpr unsigned ANNOY_MAX_VEC_SIZE = ANNS_MAX_VEC_SIZE;    // total data size
static constexpr unsigned ANNOY_DIM = ANNS_DIM;    // vec dim
static constexpr unsigned ANNOY_TOP_K = ANNS_TOP_K;    // top k

static DAnnFuncType ANNOY_FUNC_TYPE = DAnnFuncType::ANN_PREPARE_ERROR;
static const char* ANNOY_MODEL_PATH = "annoy.model";    // model file path
static const char* ANNOY_PARAM_KEY = "annoy-param";    // param key

/**
 * annoy own param
 */
static constexpr unsigned ANNOY_TREE_SIZE = 10;    // tree size
static constexpr int ANNOY_BUILD_THREAD_NUM = -1;    // annoy build model thread num, -1 as default
static constexpr int ANNOY_SEARCH_K = -1;    // provided in runtime and affects the search performance, -1 as default

#endif //GRAPHANNS_ANNOY_DEFINE_H
