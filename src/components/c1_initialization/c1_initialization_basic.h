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
#include <cassert>

#include "../components_basic.h"
#include "../../utils/utils.h"

class C1InitializationBasic : public ComponentsBasic {
protected:
    CStatus init() override {
        auto *model_param = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY)
        if (!model_param) {
            CGRAPH_RETURN_ERROR_STATUS("C1InitializationBasic init get param failed")
        }

        CStatus status = model_param->train_meta_modal1_.load(Params.GA_ALG_BASE_MODAL1_PATH_, Params.is_norm_modal1_);
        status += model_param->train_meta_modal2_.load(Params.GA_ALG_BASE_MODAL2_PATH_, Params.is_norm_modal2_);
        if (!status.isOK()) {
            return CStatus("C1InitializationBasic init load param failed");
        }
        assert(model_param->train_meta_modal1_.num == model_param->train_meta_modal2_.num);

        printf("[PATH] modal 1 vector path: %s\n", Params.GA_ALG_BASE_MODAL1_PATH_);
        printf("[PATH] modal 2 vector path: %s\n", Params.GA_ALG_BASE_MODAL2_PATH_);
        printf("[PARAM] vector num: %d\n", model_param->train_meta_modal1_.num);
        printf("[PARAM] modal 1 vector dim: %d\n", model_param->train_meta_modal1_.dim);
        printf("[PARAM] modal 2 vector dim: %d\n", model_param->train_meta_modal2_.dim);
        return CStatus();
    }

protected:
    unsigned out_degree_ = 0;        // out-degree of initial graph
    IDType cur_num_ = 0;           // data id being processed
};

#endif //GRAPHANNS_C1_INITIALIZATION_BASIC_H
