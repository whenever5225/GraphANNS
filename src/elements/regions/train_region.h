/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: train_region.h
@Time: 2022/4/19 4:31 PM
@Desc: region for index building
***************************/

#ifndef GRAPHANNS_TRAIN_REGION_H
#define GRAPHANNS_TRAIN_REGION_H

#include "../../../CGraph/src/CGraph.h"
#include "../elements_define.h"

class TrainRegion : public CGraph::GRegion {
public:
    CBool isHold() override {
        auto *m_param = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        if (nullptr == m_param) {
            CGRAPH_THROW_EXCEPTION("TrainRegion get param exception")
        }

        m_param->cur_id_++;
        return m_param->cur_id_ < m_param->train_meta_modal1_.num;
    }

    CStatus crashed(const CException& ex) override {
        return CStatus(ex.what());
    }
};

#endif //GRAPHANNS_TRAIN_REGION_H
