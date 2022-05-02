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

        num_ = model_->train_meta_.num;
        dim_ = model_->train_meta_.dim;
        data_ = model_->train_meta_.data;
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
            unsigned nid = model_->graph_n_[cur_id_][j].id_;
            float ndist = model_->graph_n_[cur_id_][j].distance_;
            model_->pool_.emplace_back(nid, ndist);
        }

        for (unsigned j = 0; j < model_->graph_n_[cur_id_].size(); j++) {
            unsigned nid = model_->graph_n_[cur_id_][j].id_;
            for (auto &nn : model_->graph_n_[nid]) {
                unsigned nnid = nn.id_;    // nnid is the id of neighbor's neighbor
                if (flags[nnid]) continue;
                flags[nnid] = true;
                DistResType dist = 0;
                dist_op_.calculate(data_ + cur_id_ * dim_, data_ + nnid * dim_,
                                  dim_, dim_, dist);
                model_->pool_.emplace_back(nnid, dist);
                if (model_->pool_.size() >= L_) break;
            }
            if (model_->pool_.size() >= L_) break;
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C2_CANDIDATE_NSSG_H
