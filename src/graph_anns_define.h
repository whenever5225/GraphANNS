/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: graph_ann_define.h
@Time: 2022/4/28 23:40
@Desc: common anns algo configuration
***************************/

#ifndef GRAPHANNS_GRAPH_ANNS_DEFINE_H
#define GRAPHANNS_GRAPH_ANNS_DEFINE_H

#include "../CGraph/src/CGraph.h"

/**
 * siftsmall
 */
const static char* GA_ALG_BASE_MODAL1_PATH = "../doc/siftsmall/siftsmall_base.fvecs";
const static char* GA_ALG_BASE_MODAL2_PATH = "../doc/siftsmall/int_attribute_siftsmall_base.ivecs";
const static char* GA_ALG_QUERY_MODAL1_PATH = "../doc/siftsmall/siftsmall_query.fvecs";
const static char* GA_ALG_QUERY_MODAL2_PATH = "../doc/siftsmall/int_attribute_siftsmall_query.ivecs";
const static char* GA_ALG_GROUNDTRUTH_PATH = "../doc/siftsmall/int_attribute_siftsmall_groundtruth.ivecs";
const static char* GA_ALG_INDEX_PATH = "../doc/siftsmall/siftsmall.index";

const static unsigned GA_NPG_L_CANDIDATE = 100;      // size of candidate set for neighbor selection
const static unsigned GA_NPG_R_NEIGHBOR = 100;       // size of neighbor set
const static unsigned GA_NPG_C_NEIGHBOR = 200;       // number of visited candidate neighbors when neighbor selection
const static unsigned GA_NPG_K_INIT_GRAPH = 20;      // number of neighbors of initial graph
const static unsigned GA_DEFAULT_THREAD_SIZE = 8;    // default thread number

/**
 * sift1m
 */
//const static char* GA_ALG_BASE_MODAL1_PATH = "/home/zjlab/ANNS/dataset/sift/sift_base.fvecs";
//const static char* GA_ALG_BASE_MODAL2_PATH = "/home/zjlab/ANNS/wmz/backup/GraphANNS/doc/sift/int_attribute_sift_base.ivecs";
//const static char* GA_ALG_QUERY_MODAL1_PATH = "/home/zjlab/ANNS/dataset/sift/sift_query.fvecs";
//const static char* GA_ALG_QUERY_MODAL2_PATH = "/home/zjlab/ANNS/wmz/backup/GraphANNS/doc/sift/int_attribute_sift_query.ivecs";
//const static char* GA_ALG_GROUNDTRUTH_PATH = "/home/zjlab/ANNS/dataset/sift/label_sift_groundtruth.ivecs";
//const static char* GA_ALG_INDEX_PATH = "../doc/siftsmall/sift1m.index";
//
//const static unsigned GA_NPG_L_CANDIDATE = 100;      // size of candidate set for neighbor selection
//const static unsigned GA_NPG_R_NEIGHBOR = 100;       // size of neighbor set
//const static unsigned GA_NPG_C_NEIGHBOR = 200;       // number of visited candidate neighbors when neighbor selection
//const static unsigned GA_NPG_K_INIT_GRAPH = 100;      // number of neighbors of initial graph
//const static unsigned GA_DEFAULT_THREAD_SIZE = 8;    // default thread number

#endif //GRAPHANNS_GRAPH_ANNS_DEFINE_H
