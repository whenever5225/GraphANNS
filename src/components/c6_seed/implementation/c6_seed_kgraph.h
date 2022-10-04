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
#include <cstring>

class C6SeedKGraph : public C6SeedBasic {
public:
    DAnnFuncType prepareParam() override {
        model_ = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY)
        auto *s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY)
        if (nullptr == model_ || nullptr == s_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }

        num_ = model_->train_meta_.num;
        dim_ = model_->train_meta_.dim;
        search_L_ = s_param->search_L;
        return DAnnFuncType::ANN_SEARCH;
    }

    CStatus search() override {
        auto *s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY)
        if (nullptr == s_param) {
            CGRAPH_RETURN_ERROR_STATUS("C6SeedKGraph search find param failed")
        }

        s_param->sp.reserve(search_L_ + 1);
        std::vector<IDType> init_ids(search_L_);

        GenRandomID(init_ids.data(), num_, search_L_);
        std::vector<char> flags(num_);
        memset(flags.data(), 0, num_ * sizeof(char));
        for (unsigned i = 0; i < search_L_; i++) {
            IDType id = init_ids[i];
            DistResType dist = 0;
            dist_op_.calculate(model_->search_meta_.data + (s_param->query_id * dim_), model_->train_meta_.data + id * dim_,
                               dim_, dim_, dist);
            s_param->sp[i] = NeighborFlag(id, dist, true);
        }

        std::sort(s_param->sp.begin(), s_param->sp.begin() + search_L_);
        return CStatus();
    }
};

#endif //GRAPHANNS_C6_SEED_KGRAPH_H
