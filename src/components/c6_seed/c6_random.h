/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c6_random.h
@Time: 2022/4/7 9:07 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_C6_RANDOM_H
#define GRAPHANNS_C6_RANDOM_H
#include "../../CGraph/src/CGraph.h"
#include "../../params/search_params.h"
#include "../../params/vector_params.h"
#include "../../distance/distance_naive.h"
#include "../c1_initialization/function/gen_random_id.h"

/**
 * seed vertex (entry) acquisition by random selection
 */

class C6Random : public CGraph::GNode {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(SearchParams, "search_info");
        return status;
    }

    CStatus run() override {
        auto s_param = CGRAPH_GET_GPARAM(SearchParams, "search_info");
        auto v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info")
        s_param->sp.resize(s_param->search_L + 1);

        std::vector<unsigned> init_ids(s_param->search_L);

        GenRandomID(init_ids.data(), v_param->num, s_param->search_L);
        std::vector<char> flags(v_param->num);
        memset(flags.data(), 0, v_param->num * sizeof(char));
        for (unsigned i = 0; i < s_param->search_L; i++) {
            unsigned id = init_ids[i];
            float dist = 0;
            CGraph::UDistanceCalculator<float, EuclideanDistance<float> > eucDist;
            eucDist.calculate(v_param->query + (s_param->query * v_param->dim), v_param->data + id * v_param->dim, v_param->dim, v_param->dim, dist);
            s_param->sp[i] = SearchParams::search_pool(id, dist, true);
        }

        std::sort(s_param->sp.begin(), s_param->sp.begin() + s_param->search_L);

        return CStatus();
    }
};
#endif //GRAPHANNS_C6_RANDOM_H
