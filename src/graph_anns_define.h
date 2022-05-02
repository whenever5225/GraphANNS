/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: graph_ann_define.h
@Time: 2022/4/28 23:40
@Desc: common anns algo configuration
***************************/

#ifndef GRAPHANNS_GRAPH_ANNS_DEFINE_H
#define GRAPHANNS_GRAPH_ANNS_DEFINE_H

const static char* GA_ALG_BASE_PATH = "../doc/siftsmall/siftsmall_base.fvecs";
const static char* GA_ALG_QUERY_PATH = "../doc/siftsmall/siftsmall_query.fvecs";
const static char* GA_ALG_GROUNDTRUTH_PATH = "../doc/siftsmall/siftsmall_groundtruth.ivecs";
const static char* GA_ALG_INDEX_PATH = "../doc/siftsmall/siftsmall.index";

const static unsigned GA_NPG_L_CANDIDATE = 100;      // size of candidate set for neighbor selection
const static unsigned GA_NPG_R_NEIGHBOR = 100;       // size of neighbor set
const static unsigned GA_NPG_C_NEIGHBOR = 200;       // number of visited candidate neighbors when neighbor selection
const static unsigned GA_NPG_K_INIT_GRAPH = 20;      // number of neighbors of initial graph

#endif //GRAPHANNS_GRAPH_ANNS_DEFINE_H
