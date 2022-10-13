/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c1_initialization_kgraph_openmp.h
@Time: 2022/10/5 10:38 AM
@Desc: OpenMP support
***************************/

#ifndef GRAPHANNS_C1_INITIALIZATION_KGRAPH_OPENMP_H
#define GRAPHANNS_C1_INITIALIZATION_KGRAPH_OPENMP_H

#if GA_USE_OPENMP

#include <omp.h>

#endif

#include "../c1_initialization_basic.h"

class C1InitializationKGraphOpenMP : public C1InitializationBasic {
public:
    DAnnFuncType prepareParam() override {
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY);
        model_ = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        if (nullptr == model_ || nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }

        num_ = model_->train_meta_modal1_.num;
        dim1_ = model_->train_meta_modal1_.dim;
        dim2_ = model_->train_meta_modal2_.dim;
        data_modal1_ = model_->train_meta_modal1_.data;
        data_modal2_ = model_->train_meta_modal2_.data;
        out_degree_ = t_param->k_init_graph;
        model_->graph_n_.resize(num_);
        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {

#pragma omp parallel for num_threads(GA_DEFAULT_THREAD_SIZE) schedule(dynamic) default(none)

        for (IDType i = 0; i < num_; i++) {
            model_->graph_n_[i].reserve(out_degree_);
            std::vector<IDType> neighbor_id(out_degree_);
            GenRandomID(neighbor_id.data(), num_, out_degree_);
            for (const IDType &id: neighbor_id) {
                if (id != cur_num_) {
                    DistResType dist = 0;
                    dist_op_.calculate(data_modal1_ + (id * dim1_),
                                       data_modal1_ + cur_num_ * dim1_,
                                       dim1_, dim1_,
                                       data_modal2_ + (id * dim2_),
                                       data_modal2_ + cur_num_ * dim2_,
                                       dim2_, dim2_, dist);
                    model_->graph_n_[i].emplace_back(id, dist);
                }
            }
        }

#if GA_USE_OPENMP
        CGraph::CGRAPH_ECHO("kgraph openmp init complete!");
#else
        CGraph::CGRAPH_ECHO("kgraph no openmp init complete!");
#endif
        return CStatus();
    }
};

#endif //GRAPHANNS_C1_INITIALIZATION_KGRAPH_OPENMP_H
