/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c2_candidate_nssg.h
@Time: 2022/4/4 4:43 PM
@Desc: get candidate neighbors via second-order neighbor propagation (like 'NSSG' algorithm)
***************************/

#ifndef GRAPHANNS_C2_CANDIDATE_NSSG_H
#define GRAPHANNS_C2_CANDIDATE_NSSG_H

#include "../c2_candidate_basic.h"

class C2CandidateNSSG : public C2CandidateBasic {
public:
    DAnnFuncType prepareParam() override {
        model_ = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        if (nullptr == model_ || nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }

        num_ = model_->train_meta_modal1_.num;
        dim1_ = model_->train_meta_modal1_.dim;
        dim2_ = model_->train_meta_modal2_.dim;
        data_modal1_ = model_->train_meta_modal1_.data;
        data_modal2_ = model_->train_meta_modal2_.data;
        cur_id_ = model_->cur_id_;

        L_ = t_param->L_candidate;
        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        model_->pool_.clear();    // model_ cannot be nullptr, because it is checked in prepareParam()
        model_->pool_.reserve(L_);
        std::vector<unsigned> flags(num_, 0);
        flags[cur_id_] = true;

        for (unsigned j = 0; j < model_->graph_n_[cur_id_].size(); j++) {
            if (flags[j]) continue;
            flags[j] = true;
            IDType nid = model_->graph_n_[cur_id_][j].id_;
            float ndist = model_->graph_n_[cur_id_][j].distance_;
            model_->pool_.emplace_back(nid, ndist);
        }

        for (unsigned j = 0; j < model_->graph_n_[cur_id_].size(); j++) {
            IDType nid = model_->graph_n_[cur_id_][j].id_;
            for (auto &nn : model_->graph_n_[nid]) {
                IDType nnid = nn.id_;    // nnid is the id of neighbor's neighbor
                if (flags[nnid]) continue;
                flags[nnid] = true;
                DistResType dist = 0;
                dist_op_.calculate(data_modal1_ + cur_id_ * dim1_, data_modal1_ + nnid * dim1_,
                                  dim1_, dim1_,
                                   data_modal2_ + cur_id_ * dim2_, data_modal2_ + nnid * dim2_,
                                  dim2_, dim2_, dist);
                model_->pool_.emplace_back(nnid, dist);
                if (model_->pool_.size() >= L_) break;
            }
            if (model_->pool_.size() >= L_) break;
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C2_CANDIDATE_NSSG_H
