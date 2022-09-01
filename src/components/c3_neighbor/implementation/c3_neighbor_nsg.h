/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c3_neighbor_nsg.h
@Time: 2022/4/7 5:20 PM
@Desc: edge selection by RNG (a strategy that considers neighbor distribution and is applied to 'NSG', 'HNSW', etc.)
***************************/

#ifndef GRAPHANNS_C3_NEIGHBOR_NSG_H
#define GRAPHANNS_C3_NEIGHBOR_NSG_H

#include "../c3_neighbor_basic.h"

class C3NeighborNSG : public C3NeighborBasic {
public:
    DAnnFuncType prepareParam() override {
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        model_ = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        if (nullptr == model_ || nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }

        num_ = model_->train_meta_modal1_.num;
        dim1_ = model_->train_meta_modal1_.dim;
        dim2_ = model_->train_meta_modal2_.dim;
        data_modal1_ = model_->train_meta_modal1_.data;
        data_modal2_ = model_->train_meta_modal2_.data;

        C_ = t_param->C_neighbor;
        R_ = t_param->R_neighbor;

        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        unsigned start = 0;
        std::sort(model_->pool_.begin(), model_->pool_.end());
        result_.clear();
        if (model_->pool_[start].id_ == cur_id_) start++;
        result_.push_back(model_->pool_[start]);

        while (result_.size() < R_ && (++start) < model_->pool_.size() && start < C_) {
            auto &p = model_->pool_[start];
            unsigned occlude = false;
            for (auto &t: result_) {
                if (p.id_ == t.id_) {
                    occlude = true;
                    break;
                }
                DistResType djk = 0;
                dist_op_.calculate(data_modal1_ + (t.id_ * dim1_),data_modal1_ + p.id_ * dim1_,
                                  dim1_, dim1_,
                                   data_modal2_ + (t.id_ * dim2_),data_modal2_ + p.id_ * dim2_,
                                  dim2_, dim2_, djk);
                if (djk < p.distance_) {
                    occlude = true;
                    break;
                }
            }
            if (!occlude) result_.push_back(p);
        }
        return CStatus();
    }


    CStatus refreshParam() override {
        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(model_)
            model_->cut_graph_.push_back(result_);
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C3_NEIGHBOR_NSG_H
