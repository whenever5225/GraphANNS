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
        auto g_param = CGRAPH_GET_GPARAM(ParamNpgTrain, GA_ALG_NPG_TRAIN_PARAM)
        if (nullptr == g_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        num_ = g_param->num;
        dim_ = g_param->dim;
        data_ = g_param->data;
        L_ = g_param->L_candidate;
        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);
        g_param->pool_m.reserve(num_);

        for (unsigned i = 0; i < num_; i++) {
            std::vector<bool> flags(num_, false);
            flags[i] = true;
            for (unsigned j = 0; j < g_param->graph_n[i].size(); j++) {
                if (flags[j]) continue;
                flags[j] = true;
                unsigned nid = g_param->graph_n[i][j].id_;
                float ndist = g_param->graph_n[i][j].distance_;
                g_param->pool_m[i].emplace_back(nid, ndist);
            }
            for (unsigned j = 0; j < g_param->graph_n[i].size(); j++) {
                unsigned nid = g_param->graph_n[i][j].id_;
                for (unsigned nn = 0; nn < g_param->graph_n[nid].size(); nn++) {
                    unsigned nnid = g_param->graph_n[nid][nn].id_;
                    if (flags[nnid]) continue;
                    flags[nnid] = true;
                    DistResType dist = 0;
                    dist_op_.calculate(data_ + i * dim_, data_ + nnid * dim_, dim_, dim_, dist);
                    g_param->pool_m[i].emplace_back(nnid, dist);
                    if (g_param->pool_m[i].size() >= L_) break;
                }
                if (g_param->pool_m[i].size() >= L_) break;
            }
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C2_CANDIDATE_NSSGV1_H
