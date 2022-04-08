/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: save_index.h
@Time: 2022/4/7 7:25 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_SAVE_INDEX_H
#define GRAPHANNS_SAVE_INDEX_H

#include "../../CGraph/src/CGraph.h"
#include "../params/alg/npg_params.h"
#include "../params/vector_params.h"
#include <fstream>

/**
 * save graph index to file
 */

class SaveIndex : public CGraph::GNode {
public:
    CStatus run() override {
        auto g_param = CGRAPH_GET_GPARAM(graph_params, "graph_info");
        auto v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info");
        auto npg_param = CGRAPH_GET_GPARAM(npg_params, "npg_info");
        std::fstream f_out(&g_param->index_path[0], std::ios::binary | std::ios::out);
        for (unsigned i = 0; i < v_param->num; i++) {
            unsigned GK = (unsigned) npg_param->cut_graph[i].size();
            std::vector<unsigned> tmp;
            for (unsigned j = 0; j < GK; j++) {
                tmp.push_back(npg_param->cut_graph[i][j].id);
            }
            f_out.write((char *) &GK, sizeof(unsigned));
            f_out.write((char *) tmp.data(), GK * sizeof(unsigned));
        }
        f_out.close();
        return CStatus();
    }
};

#endif //GRAPHANNS_SAVE_INDEX_H
