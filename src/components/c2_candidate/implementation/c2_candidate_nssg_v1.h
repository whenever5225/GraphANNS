/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c2_candidate_nssgv1.h
@Time: 2022/4/4 4:43 PM
@Desc: get candidate neighbors via second-order neighbor propagation (like 'NSSG' algorithm)
***************************/

#ifndef GRAPHANNS_C2_CANDIDATE_NSSG_V1_H
#define GRAPHANNS_C2_CANDIDATE_NSSG_V1_H

#include "../c2_candidate_basic.h"

class C2CandidateNSSGV1 : public C2CandidateNSSG {
public:
    CStatus train() override {
        model_->pool_m_.reserve(num_);

        for (IDType i = 0; i < num_; i++) {
            std::vector<bool> flags(num_, false);
            flags[i] = true;
            for (unsigned j = 0; j < model_->graph_n_[i].size(); j++) {
                if (flags[j]) continue;
                flags[j] = true;
                IDType nid = model_->graph_n_[i][j].id_;
                float ndist = model_->graph_n_[i][j].distance_;
                model_->pool_m_[i].emplace_back(nid, ndist);
            }

            for (unsigned j = 0; j < model_->graph_n_[i].size(); j++) {
                IDType nid = model_->graph_n_[i][j].id_;
                for (unsigned nn = 0; nn < model_->graph_n_[nid].size(); nn++) {
                    IDType nnid = model_->graph_n_[nid][nn].id_;
                    if (flags[nnid]) continue;
                    flags[nnid] = true;
                    DistResType dist = 0;
                    dist_op_.calculate(data_modal1_ + i * dim1_, data_modal1_ + nnid * dim1_,
                                       dim1_, dim1_,
                                       data_modal2_ + i * dim2_, data_modal2_ + nnid * dim2_,
                                       dim2_, dim2_, dist);
                    model_->pool_m_[i].emplace_back(nnid, dist);
                    if (model_->pool_m_[i].size() >= L_) break;
                }
                if (model_->pool_m_[i].size() >= L_) break;
            }
        }

        return CStatus();
    }
};

#endif //GRAPHANNS_C2_CANDIDATE_NSSG_V1_H
