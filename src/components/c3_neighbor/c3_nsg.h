/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c3_nsg.h
@Time: 2022/4/7 5:20 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_C3_NSG_H
#define GRAPHANNS_C3_NSG_H
#include "../../CGraph/src/CGraph.h"
#include "../../params/alg/npg_params.h"
#include "../../params/vector_params.h"
#include "../../distance/distance_naive.h"

/**
 * edge selection via RNG (like 'nsg' algorithm)
 */

class C3NSG : public CGraph::GNode{
public:

    CStatus run() override {
        auto npg_param = CGRAPH_GET_GPARAM(npg_params, "npg_info");
        auto v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info")

        for (unsigned i = 0; i < v_param->num; i++) {
            unsigned start = 0;
            std::sort(npg_param->pool[i].begin(), npg_param->pool[i].end());
            std::vector<graph_params::simple_neighbor> result;
            if (npg_param->pool[i][start].id == i) start++;
            result.push_back(npg_param->pool[i][start]);

            while (result.size() < npg_param->R_neighbor && (++start) < npg_param->pool[i].size() && start < npg_param->C_neighbor) {
                auto &p = npg_param->pool[i][start];
                bool occlude = false;
                for (unsigned t = 0; t < result.size(); t++) {
                    if (p.id == result[t].id) {
                        occlude = true;
                        break;
                    }
                    float djk = 0;
                    CGraph::UDistanceCalculator<float, EuclideanDistance<float> > eucDist;
                    eucDist.calculate(v_param->data + (result[t].id * v_param->dim), v_param->data + p.id * v_param->dim, v_param->dim, v_param->dim, djk);
                    if (djk < p.distance) {
                        occlude = true;
                        break;
                    }
                }
                if (!occlude) result.push_back(p);
            }

            {
                CGRAPH_PARAM_WRITE_CODE_BLOCK(npg_param);
                npg_param->cut_graph.push_back(result);
            }
        }
        return CStatus();
    }
};
#endif //GRAPHANNS_C3_NSG_H
