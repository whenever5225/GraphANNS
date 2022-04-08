/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: load_for_eva.h
@Time: 2022/4/8 4:25 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_LOAD_FOR_EVA_H
#define GRAPHANNS_LOAD_FOR_EVA_H

#include "../../CGraph/src/CGraph.h"
#include "../params/vector_params.h"
#include "read_vecs.h"

/**
 * load data for performance evaluation
 */

class LoadForEva : public CGraph::GNode {
public:
    CStatus run() override {
        auto *v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info");
        v_param->groundtruth_path = "/Users/wmz/Documents/Postgraduate/Code/dataset/siftsmall/siftsmall_groundtruth.ivecs";

        read_vecs(&v_param->groundtruth_path[0], v_param->gt, v_param->gt_num, v_param->gt_dim);
        return CStatus();
    }
};

#endif //GRAPHANNS_LOAD_FOR_EVA_H
