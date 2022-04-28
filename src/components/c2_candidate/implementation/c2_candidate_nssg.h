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
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY)
        if (nullptr == g_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        num_ = g_param->num;
        dim_ = g_param->dim;
        data_ = g_param->data;
        cur_id_ = g_param->cur_id;
        L_ = g_param->L_candidate;
        return DAnnFuncType::ANN_TRAIN;
    }


    CStatus train() override {
        auto g_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(g_param)

        g_param->pool.clear();
        g_param->pool.reserve(L_);
        std::vector<unsigned> flags(num_, 0);
        flags[cur_id_] = true;

        for (unsigned j = 0; j < g_param->graph_n[cur_id_].size(); j++) {
            if (flags[j]) continue;
            flags[j] = true;
            unsigned nid = g_param->graph_n[cur_id_][j].id_;
            float ndist = g_param->graph_n[cur_id_][j].distance_;
            g_param->pool.emplace_back(nid, ndist);
        }

        for (unsigned j = 0; j < g_param->graph_n[cur_id_].size(); j++) {
            unsigned nid = g_param->graph_n[cur_id_][j].id_;
            for (unsigned nn = 0; nn < g_param->graph_n[nid].size(); nn++) {
                unsigned nnid = g_param->graph_n[nid][nn].id_;  // nnid is the id of neighbor's neighbor
                if (flags[nnid]) continue;
                flags[nnid] = true;
                DistResType dist = 0;
                DistCalcType distOper;
                distOper.calculate(data_ + cur_id_ * dim_, data_ + nnid * dim_,
                                  dim_, dim_, dist);
                g_param->pool.emplace_back(nnid, dist);
                if (g_param->pool.size() >= L_) break;
            }
            if (g_param->pool.size() >= L_) break;
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C2_CANDIDATE_NSSG_H
