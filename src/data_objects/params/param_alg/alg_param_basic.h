/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: alg_param_basic.h
@Time: 2022/10/14 10:10 AM
@Desc:
***************************/

#ifndef GRAPHANNS_ALG_PARAM_BASIC_H
#define GRAPHANNS_ALG_PARAM_BASIC_H

#include "../basic_param.h"

struct AlgParamBasic : public BasicParam {
    unsigned top_k = Params.top_k_;

    std::vector<std::vector<IDType> > results;
    std::vector<std::vector<IDType> > results_modal1;
    std::vector<std::vector<IDType> > results_modal2;

    CVoid reset() override {
    }
};

#endif //GRAPHANNS_ALG_PARAM_BASIC_H
