/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: hnsw_algo_node.h
@Time: 2022/6/4 00:54
@Desc: 
***************************/

#ifndef GRAPHANNS_HNSW_ALGO_NODE_H
#define GRAPHANNS_HNSW_ALGO_NODE_H

#include <queue>

#include "../../../CGraph/src/CGraph.h"
#include "../../../3rd-anns/hnswlib/hnswlib/hnswalg.h"

#include "../hnsw_define.h"
#include "../param/hnsw_param.h"

class HnswAlgoNode : public CGraph::DAnnNode {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(HnswParam, HNSW_PARAM_KEY)
        auto param = CGRAPH_GET_GPARAM(HnswParam, HNSW_PARAM_KEY)
        space_ = new hnswlib::L2Space(param->dim_);    // euc distance

        if (HNSW_FUNC_TYPE == DAnnFuncType::ANN_SEARCH) {
            // only load once when mode is ANN_SEARCH
            hnsw_model_ = new hnswlib::HierarchicalNSW<HNSW_DIST_TYPE>(space_, param->ann_model_path_, false, param->max_vec_size_);
            hnsw_model_->setEf(param->ef_);
        }

        return status;
    }

    DAnnFuncType prepareParam() override {
        return HNSW_FUNC_TYPE;
    }

    CStatus train() override {
        auto param = CGRAPH_GET_GPARAM(HnswParam, HNSW_PARAM_KEY)
        if (nullptr == param) {
            CGRAPH_RETURN_ERROR_STATUS("HnswAlgoNode train param is null")
        }

        hnsw_model_ = new hnswlib::HierarchicalNSW<HNSW_DIST_TYPE>(space_, param->max_vec_size_, param->neighbor_size_, param->ef_constructor_);
        for (int i = 0; i < param->cur_vec_size_; i++) {
            hnsw_model_->addPoint((void *)param->data_[i].data(), i);
        }

        hnsw_model_->saveIndex(param->ann_model_path_);
        return CStatus();
    }

    CStatus search() override {
        auto param = CGRAPH_GET_GPARAM(HnswParam, HNSW_PARAM_KEY)
        if (nullptr == param || nullptr == hnsw_model_) {
            CGRAPH_RETURN_ERROR_STATUS("HnswAlgoNode search param is null")
        }

        auto result = hnsw_model_->searchKnn(param->query_.data(), param->top_k_);
        while (!result.empty()) {
            auto cur = result.top();
            result.pop();
            // add search result to distance_ & candidate_
            param->distance_.insert(param->distance_.begin(), cur.first);
            param->candidate_.insert(param->candidate_.begin(), (unsigned)cur.second);
        }

        return CStatus();
    }

    CStatus destroy() override {
        CGRAPH_DELETE_PTR(hnsw_model_)
        CGRAPH_DELETE_PTR(space_)
        return CStatus();
    }

private:
    hnswlib::HierarchicalNSW<HNSW_DIST_TYPE>* hnsw_model_ = nullptr;
    hnswlib::L2Space* space_ = nullptr;
};

#endif //GRAPHANNS_HNSW_ALGO_NODE_H
