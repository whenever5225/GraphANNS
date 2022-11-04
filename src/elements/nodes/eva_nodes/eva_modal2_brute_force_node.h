/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: eva_modal2_brute_force_node.h
@Time: 2022/11/1 8:49 PM
@Desc: modal2 brute force
***************************/

#ifndef GRAPHANNS_EVA_MODAL2_BRUTE_FORCE_NODE_H
#define GRAPHANNS_EVA_MODAL2_BRUTE_FORCE_NODE_H

#if GA_USE_OPENMP

#include <omp.h>

#endif

#include <cassert>
#include "../../elements_define.h"

template<typename DistCalcType = BiDistanceCalculator<DistInnerProduct, DistAttributeSimilarity>>
class EvaModal2BruteForceNode : public CGraph::GNode {
public:
    CStatus init() override {
        auto *model_param = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        if (!model_param) {
            CGRAPH_RETURN_ERROR_STATUS("EvaModal2BruteForceNode get model param failed")
        }

        CStatus status = model_param->train_meta_modal1_.load(Params.GA_ALG_BASE_MODAL1_PATH_,
                                                              Params.is_norm_modal1_);
        status += model_param->train_meta_modal2_.load(Params.GA_ALG_BASE_MODAL2_PATH_,
                                                       Params.is_norm_modal2_);
        assert(model_param->train_meta_modal1_.num == model_param->train_meta_modal2_.num);

        printf("[PATH] modal 1 vector path: %s\n", Params.GA_ALG_BASE_MODAL1_PATH_);
        printf("[PATH] modal 2 vector path: %s\n", Params.GA_ALG_BASE_MODAL2_PATH_);
        printf("[PARAM] vector num: %d\n", model_param->train_meta_modal1_.num);
        printf("[PARAM] modal 1 vector dim: %d\n", model_param->train_meta_modal1_.dim);
        printf("[PARAM] modal 2 vector dim: %d\n", model_param->train_meta_modal2_.dim);

        auto *s_param = CGRAPH_GET_GPARAM(AlgParamBasic, GA_ALG_PARAM_BASIC_KEY)
        if (!s_param) {
            CGRAPH_RETURN_ERROR_STATUS("EvaModal2BruteForceNode get search param failed")
        }

        status += model_param->search_meta_modal1_.load(Params.GA_ALG_QUERY_MODAL1_PATH_,
                                                        Params.is_norm_modal1_);
        status += model_param->search_meta_modal2_.load(Params.GA_ALG_QUERY_MODAL2_PATH_,
                                                        Params.is_norm_modal2_);
        if (Params.is_delete_id_) {
            status += model_param->delete_meta_.load(Params.GA_ALG_DELETE_ID_PATH_, 0);
            delete_num_each_query_ = model_param->delete_meta_.dim;
        }
        assert(model_param->search_meta_modal1_.num == model_param->search_meta_modal2_.num);
        assert(model_param->search_meta_modal1_.dim == model_param->train_meta_modal1_.dim);
        assert(model_param->search_meta_modal2_.dim == model_param->train_meta_modal2_.dim);
        if (!status.isOK()) {
            return CStatus("EvaModal2BruteForceNode init load param failed");
        }

        printf("[PATH] modal 1 query vector path: %s\n", model_param->search_meta_modal1_.file_path.c_str());
        printf("[PATH] modal 2 query vector path: %s\n", model_param->search_meta_modal2_.file_path.c_str());
        printf("[PARAM] query vector num: %d\n", model_param->search_meta_modal1_.num);
        printf("[PARAM] modal 1 query vector dim: %d\n", model_param->search_meta_modal1_.dim);
        printf("[PARAM] modal 2 query vector dim: %d\n", model_param->search_meta_modal2_.dim);
        num_ = model_param->train_meta_modal1_.num;
        query_num_ = model_param->search_meta_modal1_.num;
        dim1_ = model_param->train_meta_modal1_.dim;
        dim2_ = model_param->train_meta_modal2_.dim;
        dist_op_.set_weight(0, Params.w2_);
        return CStatus();
    }

    struct cmp {
        template<typename T, typename U>
        bool operator()(T const &left, U const &right) {
            if (left.first > right.first) return true;
            return false;
        }
    };

    CStatus run() override {
        auto *m_param = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY)
        auto *s_param = CGRAPH_GET_GPARAM(AlgParamBasic, GA_ALG_PARAM_BASIC_KEY);
        if (nullptr == m_param || nullptr == s_param) {
            CGRAPH_RETURN_ERROR_STATUS("EvaModal2BruteForceNode run get param failed")
        }

        s_param->results_modal2.resize(num_);
        unsigned top_k = Params.candi_top_k_;

#pragma omp parallel for num_threads(Params.thread_num_) schedule(dynamic) \
                         shared(m_param, s_param, top_k) default(none)

        for (IDType i = 0; i < query_num_; i++) {
            std::priority_queue<std::pair<DistResType, IDType>,
                    std::vector<std::pair<DistResType, IDType>>, cmp> dist_id;
            for (IDType j = 0; j < num_; j++) {
                bool is_delete = false;
                if (delete_num_each_query_) {
                    for (IDType k = 0; k < delete_num_each_query_; k++) {
                        if (j == m_param->delete_meta_.data[i * delete_num_each_query_ + k]) {
                            is_delete = true;
                            break;
                        }
                    }
                }
                if (is_delete) continue;
                DistResType dist = 0;
                dist_op_.calculate(m_param->search_meta_modal1_.data + (i * dim1_),
                                   m_param->train_meta_modal1_.data + j * dim1_,
                                   dim1_, dim1_,
                                   m_param->search_meta_modal2_.data + (i * dim2_),
                                   m_param->train_meta_modal2_.data + j * dim2_,
                                   dim2_, dim2_, dist);
                dist_id.push(std::pair<DistResType, IDType>(dist, j));
            }
            for (IDType j = 0; j < top_k; j++) {
                std::pair<DistResType, IDType> p = dist_id.top();
                dist_id.pop();
                s_param->results_modal2[i].emplace_back(p.second);
            }
        }

#if GA_USE_OPENMP
        printf("[OPENMP] brute force openmp init complete!\n");
#else
        CGraph::CGRAPH_ECHO("brute force no openmp init complete!");
#endif

        return CStatus();
    }

private:
    unsigned dim1_ = 0;
    unsigned dim2_ = 0;
    unsigned delete_num_each_query_ = 0;
    unsigned query_num_ = 0;
    unsigned num_ = 0;
    DistCalcType dist_op_;
};

#endif //GRAPHANNS_EVA_MODAL2_BRUTE_FORCE_NODE_H
