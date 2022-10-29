/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: graph_ann_define.h
@Time: 2022/4/28 23:40
@Desc: common anns algo configuration
***************************/

#ifndef GRAPHANNS_GRAPH_ANNS_DEFINE_H
#define GRAPHANNS_GRAPH_ANNS_DEFINE_H

#include <utility>

#include "../CGraph/src/CGraph.h"

struct ParamConfig {
    explicit ParamConfig() = default;

    void set_train_param(char *modal1_base_path, char *modal2_base_path, char *index_path,
                         unsigned l = 100, unsigned r = 30, unsigned c = 200, unsigned k_init_graph = 100,
                         unsigned nn_size = 50, unsigned rnn_size = 25, unsigned pool_size = 200,
                         unsigned iter = 8, unsigned sample_num = 100, float graph_quality_threshold = 0.8) {
        GA_ALG_BASE_MODAL1_PATH_ = modal1_base_path;
        GA_ALG_BASE_MODAL2_PATH_ = modal2_base_path;
        GA_ALG_INDEX_PATH_ = index_path;
        L_candidate_ = l;
        R_neighbor_ = r;
        C_neighbor_ = c;
        k_init_graph_ = k_init_graph;
        nn_size_ = nn_size;
        rnn_size_ = rnn_size;
        pool_size_ = pool_size;
        iter_ = iter;
        sample_num_ = sample_num;
        graph_quality_threshold_ = graph_quality_threshold;
    }

    void set_search_param(char *modal1_base_path, char *modal2_base_path, char *modal1_query_path,
                          char *modal2_query_path, char *gt_path, char *res_path, unsigned top_k = 1,
                          unsigned gt_k = 1, unsigned L_search = 200, char *index_path = nullptr) {
        GA_ALG_BASE_MODAL1_PATH_ = modal1_base_path;
        GA_ALG_BASE_MODAL2_PATH_ = modal2_base_path;
        GA_ALG_QUERY_MODAL1_PATH_ = modal1_query_path;
        GA_ALG_QUERY_MODAL2_PATH_ = modal2_query_path;
        GA_ALG_GROUND_TRUTH_PATH_ = gt_path;
        GA_ALG_INDEX_PATH_ = index_path;
        GA_ALG_RESULT_PATH_ = res_path;
        top_k_ = top_k;
        gt_k_ = gt_k;
        L_search_ = L_search;
    }

    void set_data_param(float w1 = -0.5, float w2 = -0.5) {
        w1_ = w1;
        w2_ = w2;
    }

    void set_general_param(unsigned thread_num = 1, unsigned is_norm_modal1 = 0, unsigned is_norm_modal2 = 0,
            unsigned is_skip = 0, unsigned skip_num = 0, unsigned is_multi_res_equal = 0) {
        thread_num_ = thread_num;
        is_norm_modal1_ = is_norm_modal1;
        is_norm_modal2_ = is_norm_modal2;
        is_skip_ = is_skip;
        skip_num_ = skip_num;
        is_multi_res_equal_ = is_multi_res_equal;
    }

public:
    char *GA_ALG_BASE_MODAL1_PATH_{};    // base vector data for modal #1
    char *GA_ALG_BASE_MODAL2_PATH_{};    // base vector data for modal #2
    char *GA_ALG_QUERY_MODAL1_PATH_{};
    char *GA_ALG_QUERY_MODAL2_PATH_{};
    char *GA_ALG_GROUND_TRUTH_PATH_{};
    char *GA_ALG_INDEX_PATH_{};
    char *GA_ALG_RESULT_PATH_{};

    unsigned L_candidate_{};
    unsigned R_neighbor_{};
    unsigned C_neighbor_{};
    unsigned k_init_graph_{};
    unsigned nn_size_{};
    unsigned rnn_size_{};
    unsigned pool_size_{};
    unsigned iter_{};
    unsigned sample_num_{};
    float graph_quality_threshold_{};

    unsigned top_k_{};
    unsigned gt_k_{};
    unsigned L_search_{};

    unsigned thread_num_{};
    unsigned is_norm_modal1_{};
    unsigned is_norm_modal2_{};
    unsigned is_skip_{};
    unsigned skip_num_{};
    unsigned is_multi_res_equal_{};

    float w1_{};
    float w2_{};
};

ParamConfig Params{};

#endif //GRAPHANNS_GRAPH_ANNS_DEFINE_H
