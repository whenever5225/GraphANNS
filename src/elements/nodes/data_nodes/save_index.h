/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: save_index.h
@Time: 2022/4/7 7:25 PM
@Desc: save graph index to file
***************************/

#ifndef GRAPHANNS_SAVE_INDEX_H
#define GRAPHANNS_SAVE_INDEX_H

#include "src/CGraph.h"
#include "../param_nodes/param_include.h"
#include <fstream>

class SaveIndex : public CGraph::GNode {
public:
    CStatus run() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param)

        std::fstream f_out(&g_param->index_path[0], std::ios::binary | std::ios::out);
        for (unsigned i = 0; i < g_param->num; i++) {
            auto GK = (unsigned) g_param->cut_graph[i].size();
            std::vector<unsigned> tmp;
            for (unsigned j = 0; j < GK; j++) {
                tmp.push_back(g_param->cut_graph[i][j].id_);
            }
            f_out.write((char *) &GK, sizeof(unsigned));
            f_out.write((char *) tmp.data(), GK * sizeof(unsigned));
        }
        f_out.close();
        return CStatus();
    }
};

#endif //GRAPHANNS_SAVE_INDEX_H
