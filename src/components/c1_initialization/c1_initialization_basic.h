/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c1_initialization_basic.h
@Time: 2022/4/11 7:04 PM
@Desc:
***************************/

#ifndef GRAPHANNS_C1_INITIALIZATION_BASIC_H
#define GRAPHANNS_C1_INITIALIZATION_BASIC_H

#include <string>

#include "../components_basic.h"
#include "../../utils/utils.h"

class C1InitializationBasic : public ComponentsBasic {
protected:
    CStatus init() override {
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        CStatus status = t_param->load(GA_ALG_BASE_PATH);
        if (!status.isOK()) {
            return CStatus("C1InitializationBasic load param failed : " + std::string(GA_ALG_BASE_PATH));
        }

        CGraph::CGRAPH_ECHO("vector path: [%s]", GA_ALG_BASE_PATH);
        CGraph::CGRAPH_ECHO("vector num: [%d]", t_param->num);
        CGraph::CGRAPH_ECHO("vector dim: [%d]", t_param->dim);
        return CStatus();
    }

protected:
    unsigned out_degree_ = 0;        // out-degree of initial graph
    unsigned cur_num_ = 0;           // number of the data being processed
};

#endif //GRAPHANNS_C1_INITIALIZATION_BASIC_H
