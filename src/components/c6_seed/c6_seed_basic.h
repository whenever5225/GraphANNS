/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c6_seed_basic.h
@Time: 2022/4/21 10:10 AM
@Desc:
***************************/

#ifndef GRAPHANNS_C6_SEED_BASIC_H
#define GRAPHANNS_C6_SEED_BASIC_H

#include "../components_basic.h"
#include "../../utils/utils.h"
#include "../../elements/elements.h"

class C6SeedBasic : public ComponentsBasic {
protected:
    CStatus init() override {
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        auto *s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY)
        if (nullptr == t_param || nullptr == s_param) {
            CGRAPH_RETURN_ERROR_STATUS("C6SeedBasic get param failed")
        }

        CStatus status = s_param->load(GA_ALG_QUERY_PATH);
        status += t_param->load(GA_ALG_BASE_PATH);
        if (!status.isOK()) {
            CGRAPH_RETURN_ERROR_STATUS("C6SeedBasic load param failed")
        }

        CGraph::CGRAPH_ECHO("vector path: [%s]", GA_ALG_BASE_PATH);
        CGraph::CGRAPH_ECHO("vector num: [%d]", t_param->num);
        CGraph::CGRAPH_ECHO("vector dim: [%d]", t_param->dim);
        return CStatus();
    }

protected:
    unsigned search_L_; // candidate pool size for search
};

#endif //GRAPHANNS_C6_SEED_BASIC_H
