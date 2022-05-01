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
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        if (nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }
        dim_ = t_param->dim;
        data_ = t_param->data;
        cur_id_ = t_param->cur_id;
        C_ = t_param->C_neighbor;
        R_ = t_param->R_neighbor;

        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(t_param)

        unsigned start = 0;
        std::sort(t_param->pool.begin(), t_param->pool.end());
        result_.clear();
        if (t_param->pool[start].id_ == cur_id_) start++;
        result_.push_back(t_param->pool[start]);

        while (result_.size() < R_ && (++start) < t_param->pool.size() &&
               start < C_) {
            auto &p = t_param->pool[start];
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
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(t_param);
        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(t_param);
            t_param->cut_graph.push_back(result_);
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C3_NEIGHBOR_NSG_H
