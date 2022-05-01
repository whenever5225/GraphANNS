/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: load_index_node.h
@Time: 2022/4/7 8:31 PM
@Desc: load graph index from file
***************************/

#ifndef GRAPHANNS_LOAD_INDEX_NODE_H
#define GRAPHANNS_LOAD_INDEX_NODE_H

#include <fstream>

#include "../../elements_define.h"
#include "src/CGraph.h"

class LoadIndexNode : public CGraph::GNode {
public:
    CStatus init() override {
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(t_param)

        std::ifstream f_in(GA_ALG_INDEX_PATH, std::ios::binary);
        if (!f_in.is_open()) {
            CGRAPH_RETURN_ERROR_STATUS("load graph error!");
        }

        while (!f_in.eof()) {
            unsigned GK = 0;
            f_in.read((char *) &GK, sizeof(unsigned));
            if (f_in.eof()) break;
            std::vector<unsigned> tmp(GK);
            f_in.read((char *) tmp.data(), GK * sizeof(unsigned));
            t_param->graph_m.push_back(tmp);
        }
        f_in.close();
        return CStatus();
    }

    CStatus run() override {
        CGRAPH_EMPTY_FUNCTION
    }
};

#endif //GRAPHANNS_LOAD_INDEX_NODE_H
