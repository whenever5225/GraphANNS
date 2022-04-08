/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: load_index.h
@Time: 2022/4/7 8:31 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_LOAD_INDEX_H
#define GRAPHANNS_LOAD_INDEX_H

#include "../../CGraph/src/CGraph.h"
#include "../params/graph_params.h"
#include <fstream>

/**
 * load graph index from file
 */

class LoadIndex : public CGraph::GNode {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(graph_params, "graph_info");
        return status;
    }

    CStatus run() override {
        auto g_param = CGRAPH_GET_GPARAM(graph_params, "graph_info");
        std::ifstream f_in(&g_param->index_path[0], std::ios::binary);
        if (!f_in.is_open()) {
            printf("load graph error!\n");
            exit(-1);
        }
        while (!f_in.eof()) {
            unsigned GK;
            f_in.read((char *) &GK, sizeof(unsigned));
            if (f_in.eof()) break;
            std::vector<unsigned> tmp(GK);
            f_in.read((char *) tmp.data(), GK * sizeof(unsigned));
            g_param->graph_m.push_back(tmp);
        }
        f_in.close();
        return CStatus();
    }
};

#endif //GRAPHANNS_LOAD_INDEX_H
