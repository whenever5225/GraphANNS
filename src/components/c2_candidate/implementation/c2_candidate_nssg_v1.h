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
        model_->pool_m.reserve(num_);

        for (unsigned i = 0; i < num_; i++) {
            std::vector<bool> flags(num_, false);
            flags[i] = true;
            for (unsigned j = 0; j < model_->graph_n[i].size(); j++) {
                if (flags[j]) continue;
                flags[j] = true;
                unsigned nid = model_->graph_n[i][j].id_;
                float ndist = model_->graph_n[i][j].distance_;
                model_->pool_m[i].emplace_back(nid, ndist);
            }
            for (unsigned j = 0; j < model_->graph_n[i].size(); j++) {
                unsigned nid = model_->graph_n[i][j].id_;
                for (unsigned nn = 0; nn < model_->graph_n[nid].size(); nn++) {
                    unsigned nnid = model_->graph_n[nid][nn].id_;
                    if (flags[nnid]) continue;
                    flags[nnid] = true;
                    DistResType dist = 0;
                    dist_op_.calculate(data_ + i * dim_, data_ + nnid * dim_, dim_, dim_, dist);
                    model_->pool_m[i].emplace_back(nnid, dist);
                    if (model_->pool_m[i].size() >= L_) break;
                }
                if (model_->pool_m[i].size() >= L_) break;
            }
        }

        return CStatus();
    }
};

#endif //GRAPHANNS_C2_CANDIDATE_NSSG_V1_H
