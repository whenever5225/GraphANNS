/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: 3rd_anns_define.h
@Time: 2022/6/12 14:41
@Desc: 
***************************/

#ifndef GRAPHANNS_3RD_ANNS_DEFINE_H
#define GRAPHANNS_3RD_ANNS_DEFINE_H

#include "anns-tools/tools_include.h"

using ANNS_DIST_TYPE = float;

/**
 * param for generate random vector
 */
static constexpr ANNS_DIST_TYPE ANNS_MIN_VALUE = 0.0;    // min data value
static constexpr ANNS_DIST_TYPE ANNS_MAX_VALUE = 1.0;    // max data value
static constexpr int ANNS_BUILD_RANDOM_SEED = 1;    // build random seed
static constexpr int ANNS_QUERY_RANDOM_SEED = 1;    // query random seed, 0 is for real random

/**
 * param for dataset and result
 */
static constexpr unsigned ANNS_DIM = 32;
static constexpr unsigned ANNS_TOP_K = 5;
static constexpr unsigned ANNS_CUR_VEC_SIZE = 5000;
static constexpr unsigned ANNS_MAX_VEC_SIZE = ANNS_CUR_VEC_SIZE;

#endif //GRAPHANNS_3RD_ANNS_DEFINE_H
