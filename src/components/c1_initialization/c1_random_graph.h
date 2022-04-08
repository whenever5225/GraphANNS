/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c1_random_graph.h
@Time: 2022/3/26 9:38 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_C1_RANDOM_GRAPH_H
#define GRAPHANNS_C1_RANDOM_GRAPH_H

#include "../../CGraph/src/CGraph.h"
#include "../../params/graph_params.h"
#include "../../params/vector_params.h"
#include "function/gen_random_id.h"

/**
 * randomly initialize a graph index
 */

class C1RandomGraph : public CGraph::GNode {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(graph_params, "graph_info");
        return status;
    }

    CStatus run() override {
        auto g_param = CGRAPH_GET_GPARAM(graph_params, "graph_info");
        auto v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info");
        unsigned num = 0;
        {
            CGRAPH_PARAM_READ_CODE_BLOCK(v_param);
            num = v_param->num;
        }
        unsigned n_num = 0;
        {
            CGRAPH_PARAM_READ_CODE_BLOCK(g_param);
            n_num = g_param->out_degree;
        }

        for (unsigned i = 0; i < num; i++) {
            std::vector<unsigned> neighbor_id(n_num);
            GenRandomID(neighbor_id.data(), num, n_num);
            unsigned j = 0;
            for (auto it = neighbor_id.begin(); it != neighbor_id.end(); j++) {
                unsigned id = neighbor_id[j];
                if (id == i) {
                    it = neighbor_id.erase(it);
                } else {
                    it++;
                }
            }
            {
                CGRAPH_PARAM_WRITE_CODE_BLOCK(g_param);
                g_param->graph_m.push_back(neighbor_id);
            }
        }

        return CStatus();
    }
};

#endif //GRAPHANNS_C1_RANDOM_GRAPH_H
