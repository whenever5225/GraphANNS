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
        /**
         * todo 这个方法的 prepareParam 方法和 C2CandidateNSSG 的完全一致
         * 如果频繁出现这种情况，是不是需要考虑以下两种方法：
         * 1，看看是不是所有的 c2节点都这样，是的话，给这个放到 c2_basic里面去
         * 2，如果不是的，仅是 nssg这种类型的算法是这样的话，是不是再建立一个文件夹，nssg
         */
        model_ = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        if (nullptr == model_ || nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }

        num_ = model_->train_data.num;
        dim_ = model_->train_data.dim;
        data_ = model_->train_data.data;

        L_ = t_param->L_candidate;
        return DAnnFuncType::ANN_TRAIN;
    }

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

#endif //GRAPHANNS_C2_CANDIDATE_NSSGV1_H
