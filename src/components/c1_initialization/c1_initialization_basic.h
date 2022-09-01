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
        auto *model_param = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY)
        if (!model_param) {
            CGRAPH_RETURN_ERROR_STATUS("C1InitializationBasic init get param failed")
        }

        CStatus status = model_param->train_meta_.load(GA_ALG_BASE_PATH);
        if (!status.isOK()) {
            return CStatus("C1InitializationBasic init load param failed : " + std::string(GA_ALG_BASE_PATH));
        }

        CGraph::CGRAPH_ECHO("vector path: [%s]", GA_ALG_BASE_PATH);
        CGraph::CGRAPH_ECHO("vector num: [%d]", model_param->train_meta_.num);
        CGraph::CGRAPH_ECHO("vector dim: [%d]", model_param->train_meta_.dim);
        return CStatus();
    }

protected:
    unsigned out_degree_ = 0;        // out-degree of initial graph
    IDType cur_num_ = 0;           // data id being processed
};

#endif //GRAPHANNS_C1_INITIALIZATION_BASIC_H
