/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: save_index_node.h
@Time: 2022/4/7 7:25 PM
@Desc: save graph index to file
***************************/

#ifndef GRAPHANNS_SAVE_INDEX_NODE_H
#define GRAPHANNS_SAVE_INDEX_NODE_H

#include <fstream>

#include "src/CGraph.h"
#include "../params/param_include.h"

class SaveIndexNode : public CGraph::GNode {
public:
    CStatus run() override {
        auto t_param =  CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(t_param)

        std::fstream f_out(GA_ALG_INDEX_PATH, std::ios::binary | std::ios::out);
        for (unsigned i = 0; i < t_param->num; i++) {
            auto GK = (unsigned) t_param->cut_graph[i].size();
            std::vector<unsigned> vec;
            vec.reserve(GK);
            for (unsigned j = 0; j < GK; j++) {
                vec.push_back(t_param->cut_graph[i][j].id_);
            }
            f_out.write((char *) &GK, sizeof(unsigned));
            f_out.write((char *) vec.data(), GK * sizeof(unsigned));
        }
        f_out.close();
        return CStatus();
    }
};

#endif //GRAPHANNS_SAVE_INDEX_NODE_H
