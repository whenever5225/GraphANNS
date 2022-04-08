/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: load_for_build.h
@Time: 2022/4/7 8:07 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_LOAD_FOR_BUILD_H
#define GRAPHANNS_LOAD_FOR_BUILD_H

#include "../../CGraph/src/CGraph.h"
#include "../params/vector_params.h"
#include "read_vecs.h"

/**
 * load data for index build
 */

class LoadForBuild : public CGraph::GNode {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(vector_params, "vector_info");
        return status;
    }

    CStatus run() override {
        auto *v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info");
        v_param->base_path = "/Users/wmz/Documents/Postgraduate/Code/dataset/siftsmall/siftsmall_base.fvecs";

        read_vecs(&v_param->base_path[0], v_param->data, v_param->num, v_param->dim);
        CGraph::CGRAPH_ECHO("vector path: [%s]", v_param->base_path.c_str());
        CGraph::CGRAPH_ECHO("vector num: [%d]", v_param->num);
        CGraph::CGRAPH_ECHO("vector dim: [%d]", v_param->dim);
        return CStatus();
    }
};

#endif //GRAPHANNS_LOAD_FOR_BUILD_H
