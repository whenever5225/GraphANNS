/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: search_region.h
@Time: 2022/4/8 10:24 AM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_SEARCH_REGION_H
#define GRAPHANNS_SEARCH_REGION_H
#include "../../CGraph/src/CGraph.h"
#include "../params/vector_params.h"
#include "../params/search_params.h"
/**
 * perform multiple queries in SearchRegion, determined by "q_num" parameter
 */
class SearchRegion : public CGraph::GRegion {
public:
    CBool isHold() override {
        auto v_param = CGRAPH_GET_GPARAM(vector_params, "vector_info");
        auto s_param = CGRAPH_GET_GPARAM(SearchParams, "search_info");
        s_param->query++;
        return s_param->query < v_param->q_num;
    }
};
#endif //GRAPHANNS_SEARCH_REGION_H
