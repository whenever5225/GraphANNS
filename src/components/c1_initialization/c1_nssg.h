/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c1_nssg.h
@Time: 2022/4/4 4:51 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_C1_NSSG_H
#define GRAPHANNS_C1_NSSG_H

#include "../../CGraph/src/CGraph.h"
#include "../../params/graph_params.h"
#include "../../params/vector_params.h"
#include "function/gen_random_id.h"
#include "../../distance/distance_naive.h"

/**
 * randomly initialize a graph index for nn-descent in 'nssg' algorithm
 */

class C1NSSG : public CGraph::GNode {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(graph_params, "graph_info");
        return status;
    }

    CStatus run() override {
        auto g_param = CGRAPH_GET_GPARAM(graph_params, "graph_info");
        auto v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info");

        g_param->graph_n.resize(v_param->num);
        for (unsigned i = 0; i < v_param->num; i++) {
            g_param->graph_n[i].reserve(g_param->out_degree);
            std::vector<unsigned> neighbor_id(g_param->out_degree);
            GenRandomID(neighbor_id.data(), v_param->num, g_param->out_degree);
            for (auto it = neighbor_id.begin(); it != neighbor_id.end(); it++) {
                unsigned id = *it;
                if (id != i) {
                    float dist = 0;
                    CGraph::UDistanceCalculator<float, EuclideanDistance<float> > eucDist;
                    eucDist.calculate(v_param->data + (*it * v_param->dim), v_param->data + i * v_param->dim, v_param->dim, v_param->dim, dist);
                    g_param->graph_n[i].emplace_back(*it, dist);
                }
            }
        }

        return CStatus();
    }
};

#endif //GRAPHANNS_C1_NSSG_H
