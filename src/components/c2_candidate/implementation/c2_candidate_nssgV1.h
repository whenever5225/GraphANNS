/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c2_candidate_nssgv1.h
@Time: 2022/4/4 4:43 PM
@Desc: get candidate neighbors via second-order neighbor propagation (like 'NSSG' algorithm)
***************************/

#ifndef GRAPHANNS_C2_CANDIDATE_NSSGV1_H
#define GRAPHANNS_C2_CANDIDATE_NSSGV1_H

#include "../c2_candidate_basic.h"

class C2CandidateNSSGV1 : public C2CandidateBasic {
public:
    DAnnFuncType prepareParam() override {
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        if (nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        num_ = t_param->num;
        dim_ = t_param->dim;
        data_ = t_param->data;
        L_ = t_param->L_candidate;
        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        t_param->pool_m.reserve(num_);

        for (unsigned i = 0; i < num_; i++) {
            std::vector<bool> flags(num_, false);
            flags[i] = true;
            for (unsigned j = 0; j < t_param->graph_n[i].size(); j++) {
                if (flags[j]) continue;
                flags[j] = true;
                unsigned nid = t_param->graph_n[i][j].id_;
                float ndist = t_param->graph_n[i][j].distance_;
                t_param->pool_m[i].emplace_back(nid, ndist);
            }
            for (unsigned j = 0; j < t_param->graph_n[i].size(); j++) {
                unsigned nid = t_param->graph_n[i][j].id_;
                for (unsigned nn = 0; nn < t_param->graph_n[nid].size(); nn++) {
                    unsigned nnid = t_param->graph_n[nid][nn].id_;
                    if (flags[nnid]) continue;
                    flags[nnid] = true;
                    DistResType dist = 0;
                    dist_op_.calculate(data_ + i * dim_, data_ + nnid * dim_, dim_, dim_, dist);
                    t_param->pool_m[i].emplace_back(nnid, dist);
                    if (t_param->pool_m[i].size() >= L_) break;
                }
                if (t_param->pool_m[i].size() >= L_) break;
            }
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C2_CANDIDATE_NSSGV1_H
