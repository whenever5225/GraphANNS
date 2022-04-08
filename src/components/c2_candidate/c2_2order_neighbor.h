/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c2_2order_neighbor.h
@Time: 2022/4/4 4:43 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_C2_2ORDER_NEIGHBOR_H
#define GRAPHANNS_C2_2ORDER_NEIGHBOR_H
#include "../../CGraph/src/CGraph.h"
#include "../../params/alg/npg_params.h"
#include "../../params/vector_params.h"
#include "../../distance/distance_naive.h"

/**
 * get candidate neighbors via second-order neighbor propagation
 */

class C2TwoOrderNeighbor : public CGraph::GNode{
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(npg_params, "npg_info");
        return status;

    }

    CStatus run() override {
        auto v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info");
        auto g_param = CGRAPH_GET_GPARAM(graph_params, "graph_info");
        auto npg_param = CGRAPH_GET_GPARAM(npg_params, "npg_info")
        npg_param->pool.resize(v_param->num);
        for (unsigned i = 0; i < v_param->num; i++) {
            std::vector<bool> flags(v_param->num, false);
            flags[i] = true;
            for (unsigned j = 0; j < g_param->graph_n[i].size(); j++) {
                if (flags[j]) continue;
                flags[j] = true;
                unsigned nid = g_param->graph_n[i][j].id;
                float ndist = g_param->graph_n[i][j].distance;
                npg_param->pool[i].emplace_back(nid, ndist);
            }
            for (unsigned j = 0; j < g_param->graph_n[i].size(); j++) {
                unsigned nid = g_param->graph_n[i][j].id;
                for (unsigned nn = 0; nn < g_param->graph_n[nid].size(); nn++) {
                    unsigned nnid = g_param->graph_n[nid][nn].id;
                    if (flags[nnid]) continue;
                    flags[nnid] = true;
                    float dist = 0;
                    CGraph::UDistanceCalculator<float, EuclideanDistance<float> > eucDist;
                    eucDist.calculate(v_param->data + i * v_param->dim, v_param->data + nnid * v_param->dim, v_param->dim, v_param->dim, dist);
                    npg_param->pool[i].emplace_back(nnid, dist);
                    if (npg_param->pool[i].size() >= npg_param->L_candidate) break;
                }
                if (npg_param->pool[i].size() >= npg_param->L_candidate) break;
            }
        }
        return CStatus();
    }
};
#endif //GRAPHANNS_C2_2ORDER_NEIGHBOR_H
