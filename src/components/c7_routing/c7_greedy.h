/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c7_greedy.h
@Time: 2022/4/8 8:37 AM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_C7_GREEDY_H
#define GRAPHANNS_C7_GREEDY_H
#include "../../CGraph/src/CGraph.h"
#include "../../params/search_params.h"
#include "../../params/vector_params.h"
#include "../../params/graph_params.h"
#include "../../distance/distance_naive.h"
#include "function/insert_into_pool.h"

/**
 * greedy route
 */

class C7Greedy : public CGraph::GNode {
public:
    CStatus run() override {
        auto s_param = CGRAPH_GET_GPARAM(SearchParams, "search_info");
        auto v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info");
        auto g_param = CGRAPH_GET_GPARAM(graph_params, "graph_info");
        const auto L = s_param->search_L;
        const auto K = s_param->top_k;

        std::vector<char> flags(v_param->num, 0);
        std::vector<unsigned> res;

        int k = 0;
        while (k < (int) L) {
            int nk = L;

            if (s_param->sp[k].flag) {
                s_param->sp[k].flag = false;
                unsigned n = s_param->sp[k].id;

                for (unsigned m = 0; m < g_param->graph_m[n].size(); ++m) {
                    unsigned id = g_param->graph_m[n][m];

                    if (flags[id])continue;
                    flags[id] = 1;

                    float dist = 0;
                    CGraph::UDistanceCalculator<float, EuclideanDistance<float> > eucDist;
                    eucDist.calculate(v_param->query + (s_param->query * v_param->dim), v_param->data + id * v_param->dim, v_param->dim, v_param->dim, dist);

                    if (dist >= s_param->sp[L - 1].distance) continue;
                    SearchParams::search_pool nn(id, dist, true);
                    int r = InsertIntoPool(s_param->sp.data(), L, nn);

                    if (r < nk)nk = r;
                }
            }
            if (nk <= k)k = nk;
            else ++k;
        }

        res.resize(K);
        for (size_t i = 0; i < K; i++) {
            res[i] = s_param->sp[i].id;
        }
        s_param->results.push_back(res);
        return CStatus();
    }
};
#endif //GRAPHANNS_C7_GREEDY_H
