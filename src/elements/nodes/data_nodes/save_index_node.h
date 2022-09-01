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

#include "../../../../CGraph/src/CGraph.h"
#include "../../elements_define.h"

class SaveIndexNode : public CGraph::GNode {
public:
    CStatus run() override {
        CGRAPH_EMPTY_FUNCTION
    }

    CStatus destroy() override {
        auto m_param = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(m_param)

        std::fstream f_out(GA_ALG_INDEX_PATH, std::ios::binary | std::ios::out);
        for (unsigned i = 0; i < m_param->train_meta_.num; i++) {
            auto GK = (unsigned) m_param->cut_graph_[i].size();
            std::vector<IDType> vec;
            vec.reserve(GK);
            for (unsigned j = 0; j < GK; j++) {
                vec.push_back(m_param->cut_graph_[i][j].id_);
            }
            f_out.write((char *) &GK, sizeof(unsigned));
            f_out.write((char *) vec.data(), GK * sizeof(IDType));
        }
        f_out.close();
        return CStatus();
    }
};

#endif //GRAPHANNS_SAVE_INDEX_NODE_H
