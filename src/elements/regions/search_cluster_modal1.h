/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: search_cluster_modal1.h
@Time: 2022/11/1 7:31 PM
@Desc: search cluster modal1
***************************/

#ifndef GRAPHANNS_SEARCH_CLUSTER_MODAL1_H
#define GRAPHANNS_SEARCH_CLUSTER_MODAL1_H

#include "../../../CGraph/src/CGraph.h"
#include "../elements_define.h"

class SearchClusterModal1 : public CGraph::GCluster {
public:
    CBool isHold() override {
        auto *m_param = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        auto *s_param = CGRAPH_GET_GPARAM(NPGSearchParam, GA_ALG_NPG_SEARCH_PARAM_KEY);
        if (nullptr == m_param || nullptr == s_param) {
            /**
             * throw exception, CGraph can catch this exception automic
             */
            CGRAPH_THROW_EXCEPTION("SearchClusterModal1 isHold get param failed")
        }

        s_param->modal1_query_id++;
        return s_param->modal1_query_id < m_param->search_meta_modal1_.num;
    }


    CStatus crashed(const CException& ex) override {
        /**
         * this function can help you catch exception,
         * and you can transfer your exception info into other error code & error info
         */
        return CStatus(ex.what());
    }
};

#endif //GRAPHANNS_SEARCH_CLUSTER_MODAL1_H
