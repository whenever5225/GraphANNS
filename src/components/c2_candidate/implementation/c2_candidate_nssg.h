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
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        if (nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        num_ = t_param->num;
        dim_ = t_param->dim;
        data_ = t_param->data;
        cur_id_ = t_param->cur_id;
        L_ = t_param->L_candidate;
        return DAnnFuncType::ANN_TRAIN;
    }


    CStatus train() override {
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(t_param)

        t_param->pool.clear();
        t_param->pool.reserve(L_);
        std::vector<unsigned> flags(num_, 0);
        flags[cur_id_] = true;

        for (unsigned j = 0; j < t_param->graph_n[cur_id_].size(); j++) {
            if (flags[j]) continue;
            flags[j] = true;
            unsigned nid = t_param->graph_n[cur_id_][j].id_;
            float ndist = t_param->graph_n[cur_id_][j].distance_;
            t_param->pool.emplace_back(nid, ndist);
        }

        for (unsigned j = 0; j < t_param->graph_n[cur_id_].size(); j++) {
            unsigned nid = t_param->graph_n[cur_id_][j].id_;
            for (unsigned nn = 0; nn < t_param->graph_n[nid].size(); nn++) {
                unsigned nnid = t_param->graph_n[nid][nn].id_;  // nnid is the id of neighbor's neighbor
                if (flags[nnid]) continue;
                flags[nnid] = true;
                DistResType dist = 0;
                dist_op_.calculate(data_ + cur_id_ * dim_, data_ + nnid * dim_,
                                  dim_, dim_, dist);
                t_param->pool.emplace_back(nnid, dist);
                if (t_param->pool.size() >= L_) break;
            }
            if (t_param->pool.size() >= L_) break;
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C2_CANDIDATE_NSSG_H
