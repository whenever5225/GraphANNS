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

class C6SeedKGraph : public C6SeedBasic {
public:
    DAnnFuncType prepareParam() override {
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        auto *s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY);
        if (nullptr == t_param || nullptr == s_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }

        num_ = s_param->num;
        dim_ = s_param->dim;
        search_L_ = s_param->search_L;
        return DAnnFuncType::ANN_SEARCH;
    }

    CStatus search() override {
        /**
         * todo 确认，这个是不是 search的参数鸭，不然要出事的
         */
        auto *s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY);
        CGRAPH_ASSERT_NOT_NULL(s_param)

        s_param->sp.reserve(search_L_ + 1);
        std::vector<unsigned> init_ids(search_L_);

        GenRandomID(init_ids.data(), num_, search_L_);
        std::vector<char> flags(num_);
        memset(flags.data(), 0, s_param->num * sizeof(char));
        for (unsigned i = 0; i < search_L_; i++) {
            unsigned id = init_ids[i];
            DistResType dist = 0;
            dist_op_.calculate(s_param->query + (s_param->query_id * dim_), s_param->data + id * dim_,
                              dim_, dim_, dist);
            s_param->sp[i] = NeighborFlag(id, dist, true);
        }

        std::sort(s_param->sp.begin(), s_param->sp.begin() + search_L_);

        return CStatus();
    }
};

#endif //GRAPHANNS_C6_SEED_KGRAPH_H
