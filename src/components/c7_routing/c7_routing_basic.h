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
    VecValType1 *query_modal1_ = nullptr;    // query data
    VecValType2 *query_modal2_ = nullptr;    // query data
    unsigned query_id_; // current query id
    unsigned query_id_modal1_; // current modal1 query id
    unsigned query_id_modal2_; // current modal2 query id
    std::vector<IDType> res_modal1_; // current modal1 query result
    std::vector<IDType> res_modal2_; // current modal2 query result
    std::vector<IDType> res_; // current query result
    unsigned delete_num_each_query_ = 0;
};

#endif //GRAPHANNS_C7_ROUTING_BASIC_H
