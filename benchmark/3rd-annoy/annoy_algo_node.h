/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: annoy_node.h
@Time: 2022/5/21 15:11
@Desc: 
***************************/

#ifndef GRAPHANNS_ANNOY_ALGO_NODE_H
#define GRAPHANNS_ANNOY_ALGO_NODE_H

#include "../CGraph/src/CGraph.h"
#include "annoy_param.h"
#include "../../3rd-anns/annoy/src/annoylib.h"
#include "../../3rd-anns/annoy/src/kissrandom.h"

class AnnoyAlgoNode : public CGraph::DAnnNode {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(AnnoyParam, ANNOY_PARAM_KEY);
        auto param = CGRAPH_GET_GPARAM(AnnoyParam, ANNOY_PARAM_KEY);
        annoy_model_ = new Annoy::AnnoyIndex<int, ANNOY_DIST_TYPE, Annoy::Angular, Annoy::Kiss32Random,
                Annoy::AnnoyIndexSingleThreadedBuildPolicy>((int)param->dim_);
        return CStatus();
    }

    DAnnFuncType prepareParam() override {
        // only load once when mode is ANN_SEARCH
        if (ANNOY_FUNC_TYPE == DAnnFuncType::ANN_SEARCH) {
            auto param = CGRAPH_GET_GPARAM(AnnoyParam, ANNOY_PARAM_KEY);
            if (!annoy_model_->load(param->ann_model_path_.c_str())) {
                CGRAPH_THROW_EXCEPTION("please train a model before load it")
            }
        }

        return ANNOY_FUNC_TYPE;
    }

    CStatus train() override {
        CGraph::CGRAPH_ECHO("AnnoyAlgoNode train start ... ");
        auto param = CGRAPH_GET_GPARAM(AnnoyParam, ANNOY_PARAM_KEY);
        if (nullptr == param || nullptr == annoy_model_) {
            CGRAPH_RETURN_ERROR_STATUS("AnnoyAlgoNode train input is nullptr")
        }

        std::vector<std::vector<ANNOY_DIST_TYPE> > data;
        // build random data
        CGraph::URandom<ANNOY_DIST_TYPE, ANNOY_BUILD_RANDOM_SEED>::generate(data, param->max_vec_size_, param->dim_, ANNOY_MIN_VALUE, ANNOY_MAX_VALUE);
        for (int i = 0; i < param->max_vec_size_; i++) {
            annoy_model_->add_item(i, data[i].data());
        }

        bool result = annoy_model_->build(param->tree_size_);
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

        std::vector<ANNOY_DIST_TYPE> query;
        // build a random node for query
        CGraph::URandom<ANNOY_DIST_TYPE, ANNOY_QUERY_RANDOM_SEED>::generate(query, param->dim_, ANNOY_MIN_VALUE, ANNOY_MAX_VALUE);
        annoy_model_->get_nns_by_vector(query.data(), ANNOY_TOP_K, param->search_k_, &(param->candidate_), &(param->distance_));

        CGraph::CGRAPH_ECHO("AnnoyAlgoNode search finish ... ");
        return CStatus();
    }

    /**
     * handle exception info, as a error-code, if happened
     * @param ex
     * @return
     */
    CStatus crashed(const CException& ex) override {
        return CStatus(ex.what());
    }

    ~AnnoyAlgoNode() override {
        CGRAPH_DELETE_PTR(annoy_model_)
    }

private:
    Annoy::AnnoyIndex<int, ANNOY_DIST_TYPE, Annoy::Angular, Annoy::Kiss32Random, Annoy::AnnoyIndexSingleThreadedBuildPolicy> *annoy_model_ = nullptr;
};

#endif //GRAPHANNS_ANNOY_ALGO_NODE_H
