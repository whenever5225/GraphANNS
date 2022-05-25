/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: annoy_node.h
@Time: 2022/5/21 15:11
@Desc: 
***************************/

#ifndef GRAPHANNS_ANNOY_ALGO_NODE_H
#define GRAPHANNS_ANNOY_ALGO_NODE_H

#include "src/CGraph.h"

#include "../param/annoy_param.h"
#include "../../../3rd-anns/annoy/src/annoylib.h"
#include "../../../3rd-anns/annoy/src/kissrandom.h"

class AnnoyAlgoNode : public CGraph::DAnnNode {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(AnnoyParam, ANNOY_PARAM_KEY);
        auto param = CGRAPH_GET_GPARAM(AnnoyParam, ANNOY_PARAM_KEY);
        annoy_model_ = new Annoy::AnnoyIndex<int, ANNOY_DIST_TYPE, Annoy::Angular, Annoy::Kiss32Random,
                Annoy::AnnoyIndexSingleThreadedBuildPolicy>((int)param->dim_);

        if (ANNOY_FUNC_TYPE == DAnnFuncType::ANN_SEARCH) {
            // only load once when mode is ANN_SEARCH
            if (!annoy_model_->load(param->ann_model_path_.c_str())) {
                CGRAPH_RETURN_ERROR_STATUS("please train a model before load it")
            }
        }
        return status;
    }

    DAnnFuncType prepareParam() override {
        return ANNOY_FUNC_TYPE;
    }

    CStatus train() override {
        CGraph::CGRAPH_ECHO("AnnoyAlgoNode train start ... ");
        auto param = CGRAPH_GET_GPARAM(AnnoyParam, ANNOY_PARAM_KEY);
        if (nullptr == param || nullptr == annoy_model_) {
            CGRAPH_RETURN_ERROR_STATUS("AnnoyAlgoNode train input is nullptr")
        }

        for (int i = 0; i < param->max_vec_size_; i++) {
            annoy_model_->add_item(i, param->data_[i].data());
        }

        bool result = annoy_model_->build(param->tree_size_, param->build_thread_num_);
        if (!result) {
            CGRAPH_RETURN_ERROR_STATUS("AnnoyAlgoNode train build model failed");
        }

        result = annoy_model_->save(param->ann_model_path_.c_str());
        if (!result) {
            CGRAPH_RETURN_ERROR_STATUS("AnnoyAlgoNode train save model failed");
        }

        CGraph::CGRAPH_ECHO("AnnoyAlgoNode train finish ... ");
        return CStatus();
    }

    CStatus search() override {
        CGraph::CGRAPH_ECHO("AnnoyAlgoNode search start ... ");
        auto param = CGRAPH_GET_GPARAM(AnnoyParam, ANNOY_PARAM_KEY);
        if (nullptr == param || nullptr == annoy_model_) {
            CGRAPH_RETURN_ERROR_STATUS("AnnoyAlgoNode search input is nullptr")
        }

        annoy_model_->get_nns_by_vector(param->query_.data(), ANNOY_TOP_K, param->search_k_, &(param->candidate_), &(param->distance_));

        CGraph::CGRAPH_ECHO("AnnoyAlgoNode search finish ... ");
        return CStatus();
    }

    ~AnnoyAlgoNode() override {
        CGRAPH_DELETE_PTR(annoy_model_)
    }

private:
    Annoy::AnnoyIndex<int, ANNOY_DIST_TYPE, Annoy::Angular, Annoy::Kiss32Random, Annoy::AnnoyIndexSingleThreadedBuildPolicy> *annoy_model_ = nullptr;
};

#endif //GRAPHANNS_ANNOY_ALGO_NODE_H
