/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c6_seed_kgraph.h
@Time: 2022/4/7 9:07 PM
@Desc: seed vertex (entry) acquisition by random selection (like 'KGraph' algorithm)
***************************/

#ifndef GRAPHANNS_C6_SEED_KGRAPH_H
#define GRAPHANNS_C6_SEED_KGRAPH_H

#include "../c6_seed_basic.h"
#include "../../../elements/nodes/param_nodes/param_include.h"
#include "../../../utils/utils_include.h"

class C6SeedKGraph : public C6SeedBasic {
public:
    DAnnFuncType prepareParam() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        if (nullptr == g_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        num_ = g_param->num;
        dim_ = g_param->dim;
        search_L_ = g_param->search_L;
        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(g_param)
        g_param->sp.reserve(search_L_ + 1);

        std::vector<unsigned> init_ids(search_L_);

        GenRandomID(init_ids.data(), num_, search_L_);
        std::vector<char> flags(num_);
        memset(flags.data(), 0, g_param->num * sizeof(char));
        for (unsigned i = 0; i < search_L_; i++) {
            unsigned id = init_ids[i];
            DistResType dist = 0;
            eucDist.calculate(g_param->query + (g_param->query_id * dim_), g_param->data + id * dim_,
                              dim_, dim_, dist);
            g_param->sp[i] = SearchPool(id, dist, true);
        }

        std::sort(g_param->sp.begin(), g_param->sp.begin() + search_L_);

        return CStatus();
    }
};

#endif //GRAPHANNS_C6_SEED_KGRAPH_H
