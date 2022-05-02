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

        num_ = model_->train_data.num;
        dim_ = model_->train_data.dim;
        data_ = model_->train_data.data;

        C_ = t_param->C_neighbor;
        R_ = t_param->R_neighbor;

        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        unsigned start = 0;
        std::sort(model_->pool.begin(), model_->pool.end());
        result_.clear();
        if (model_->pool[start].id_ == cur_id_) start++;
        result_.push_back(model_->pool[start]);

        while (result_.size() < R_ && (++start) < model_->pool.size() && start < C_) {
            auto &p = model_->pool[start];
            unsigned occlude = false;
            for (auto &t: result_) {
                if (p.id_ == t.id_) {
                    occlude = true;
                    break;
                }
                DistResType djk = 0;
                dist_op_.calculate(data_ + (t.id_ * dim_),
                                  data_ + p.id_ * dim_, dim_, dim_, djk);
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
            model_->cut_graph.push_back(result_);
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C3_NEIGHBOR_NSG_H
