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

        CStatus status = model_param->train_meta_modal1_.load(GA_ALG_BASE_MODAL1_PATH);
        status += model_param->train_meta_modal2_.load(GA_ALG_BASE_MODAL2_PATH);
        if (!status.isOK()) {
            return CStatus("C1InitializationBasic init load param failed");
        }
        assert(model_param->train_meta_modal1_.num == model_param->train_meta_modal2_.num);

        CGraph::CGRAPH_ECHO("modal 1 vector path: [%s]", GA_ALG_BASE_MODAL1_PATH);
        CGraph::CGRAPH_ECHO("modal 2 vector path: [%s]", GA_ALG_BASE_MODAL2_PATH);
        CGraph::CGRAPH_ECHO("vector num: [%d]", model_param->train_meta_modal1_.num);
        CGraph::CGRAPH_ECHO("modal 1 vector dim: [%d]", model_param->train_meta_modal1_.dim);
        CGraph::CGRAPH_ECHO("modal 2 vector dim: [%d]", model_param->train_meta_modal2_.dim);
        return CStatus();
    }

protected:
    unsigned out_degree_ = 0;        // out-degree of initial graph
    IDType cur_num_ = 0;           // data id being processed
};

#endif //GRAPHANNS_C1_INITIALIZATION_BASIC_H
