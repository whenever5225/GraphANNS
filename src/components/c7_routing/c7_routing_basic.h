/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c7_routing_basic.h
@Time: 2022/4/21 10:22 AM
@Desc:
***************************/

#ifndef GRAPHANNS_C7_ROUTING_BASIC_H
#define GRAPHANNS_C7_ROUTING_BASIC_H

#include "../components_basic.h"
#include "../../utils/utils.h"

class C7RoutingBasic : public ComponentsBasic {
protected:
    unsigned search_L_; // candidate pool size for search
    unsigned K_;    // top-k for search
    VecValType *query_ = nullptr;    // query data
    unsigned query_id_; // current query id
    std::vector<unsigned> res_; // current query result
};

#endif //GRAPHANNS_C7_ROUTING_BASIC_H
