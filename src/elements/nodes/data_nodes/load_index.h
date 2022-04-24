/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: load_index.h
@Time: 2022/4/7 8:31 PM
@Desc: load graph index from file
***************************/

#ifndef GRAPHANNS_LOAD_INDEX_H
#define GRAPHANNS_LOAD_INDEX_H

#include "src/CGraph.h"
#include "../param_nodes/param_include.h"
#include <fstream>

class LoadIndex : public CGraph::GNode {
public:
    CStatus run() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param)

        std::ifstream f_in(&g_param->index_path[0], std::ios::binary);
        if (!f_in.is_open()) {
            CStatus("load graph error!");
        }
        while (!f_in.eof()) {
            unsigned GK = 0;
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
