/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: annoy_define.h
@Time: 2022/5/21 15:58
@Desc: 
***************************/

#ifndef GRAPHANNS_ANNOY_DEFINE_H
#define GRAPHANNS_ANNOY_DEFINE_H

using ANNOY_DIST_TYPE = float;

static const char* ANNOY_MODEL_PATH = "annoy.model";    // model file path
static const char* ANNOY_PARAM_KEY = "annoy-param";    // param key
static constexpr DAnnFuncType ANNOY_FUNC_TYPE = DAnnFuncType::ANN_TRAIN;    // function type, param in [ANN_TRAIN, ANN_SEARCH]

static constexpr unsigned ANNOY_MAX_VEC_SIZE = 1000;    // total data size
static constexpr unsigned ANNOY_DIM = 16;    // vec dim
static constexpr unsigned ANNOY_TREE_SIZE = 10;    // tree size
static constexpr unsigned ANNOY_TOP_K = 5;    // top k
static constexpr int ANNOY_SEARCH_K = -1;    // provided in runtime and affects the search performance, -1 as default

static constexpr ANNOY_DIST_TYPE ANNOY_MIN_VALUE = 0.0;    // min data value
static constexpr ANNOY_DIST_TYPE ANNOY_MAX_VALUE = 1.0;    // max data value
static constexpr int ANNOY_BUILD_RANDOM_SEED = 1;    // build random seed
static constexpr int ANNOY_QUERY_RANDOM_SEED = 0;    // query random seed, 0 is for real random

#endif //GRAPHANNS_ANNOY_DEFINE_H
