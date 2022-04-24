/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c1_initialization_basic.h
@Time: 2022/4/11 7:04 PM
@Desc:
***************************/

#ifndef GRAPHANNS_C1_INITIALIZATION_BASIC_H
#define GRAPHANNS_C1_INITIALIZATION_BASIC_H

#include "../../CGraph/src/CGraph.h"

class C1InitializationBasic : public CGraph::DAnnNode {
protected:
    unsigned num_ = 0;  // number of vector
    unsigned dim_ = 0;  // dimensionality of vector
    VecValType *data_ = nullptr;   // vector data
    unsigned out_degree_ = 0;   // out-degree of initial graph

    unsigned cur_num_ = 0;  // number of the data being processed

};

#endif //GRAPHANNS_C1_INITIALIZATION_BASIC_H
