/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c7_routing_basic.h
@Time: 2022/4/21 10:22 AM
@Desc:
***************************/

#ifndef GRAPHANNS_C7_ROUTING_BASIC_H
#define GRAPHANNS_C7_ROUTING_BASIC_H

#include "../../CGraph/src/CGraph.h"

class C7RoutingBasic : public CGraph::DAnnNode {
protected:
    unsigned num_ = 0;  // number of vector
    unsigned dim_ = 0;  // dimensionality of vector
    VecValType *data_ = nullptr;   // vector data
    unsigned search_L_; // candidate pool size for search
    unsigned K_;    // top-k for search
    VecValType *query_ = nullptr;    // query data
    unsigned query_id_; // current query id
    std::vector<unsigned> res_; // current query result

    int InsertIntoPool(SearchPool *addr, unsigned K, SearchPool nn) {
        // find the location to insert
        left_ = 0, right_ = K - 1;
        if (addr[left_].distance > nn.distance) {
            memmove((char *) &addr[left_ + 1], &addr[left_], K * sizeof(SearchPool));
            addr[left_] = nn;
            return left_;
        }
        if (addr[right_].distance < nn.distance) {
            addr[K] = nn;
            return K;
        }
        while (left_ < right_ - 1) {
            int mid = (left_ + right_) / 2;
            if (addr[mid].distance > nn.distance) right_ = mid;
            else left_ = mid;
        }
        //check equal ID

        while (left_ > 0) {
            if (addr[left_].distance < nn.distance) break;
            if (addr[left_].id == nn.id) return K + 1;
            left_--;
        }
        if (addr[left_].id == nn.id || addr[right_].id == nn.id) return K + 1;
        memmove((char *) &addr[right_ + 1], &addr[right_], (K - right_) * sizeof(SearchPool));
        addr[right_] = nn;
        return right_;
    }

private:
    int right_ = 0;
    int left_ = 0;
};

#endif //GRAPHANNS_C7_ROUTING_BASIC_H
