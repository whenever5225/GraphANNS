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
        auto *s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY)
        model_ = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        if (nullptr == model_ || nullptr == s_param) {
            CGRAPH_RETURN_ERROR_STATUS("C6SeedBasic get param failed")
        }

        CStatus status = model_->search_meta_modal1_.load(Params.GA_ALG_QUERY_MODAL1_PATH_,
                                                          Params.is_norm_modal1_);
        status += model_->search_meta_modal2_.load(Params.GA_ALG_QUERY_MODAL2_PATH_,
                                                   Params.is_norm_modal2_);
        assert(model_->search_meta_modal1_.num == model_->search_meta_modal2_.num);
        status += model_->train_meta_modal1_.load(Params.GA_ALG_BASE_MODAL1_PATH_, Params.is_norm_modal1_);
        status += model_->train_meta_modal2_.load(Params.GA_ALG_BASE_MODAL2_PATH_, Params.is_norm_modal2_);
        if (Params.is_delete_id_) {
            status += model_->delete_meta_.load(Params.GA_ALG_DELETE_ID_PATH_, 0);
            delete_num_each_query_ = model_->delete_meta_.dim;
        }
        assert(model_->train_meta_modal1_.num == model_->train_meta_modal2_.num);
        assert(model_->search_meta_modal1_.dim == model_->train_meta_modal1_.dim);
        assert(model_->search_meta_modal2_.dim == model_->train_meta_modal2_.dim);
        if (!status.isOK()) {
            CGRAPH_RETURN_ERROR_STATUS("C6SeedBasic load param failed")
        }

        printf("[PATH] modal 1 query vector path: %s\n", model_->search_meta_modal1_.file_path.c_str());
        printf("[PATH] modal 2 query vector path: %s\n", model_->search_meta_modal2_.file_path.c_str());
        printf("[PARAM] query vector num: %d\n", model_->search_meta_modal1_.num);
        printf("[PARAM] modal 1 query vector dim: %d\n", model_->search_meta_modal1_.dim);
        printf("[PARAM] modal 2 query vector dim: %d\n", model_->search_meta_modal2_.dim);
        return CStatus();
    }

protected:
    unsigned search_L_; // candidate pool size for search
    unsigned delete_num_each_query_ = 0;
};

#endif //GRAPHANNS_C6_SEED_BASIC_H
