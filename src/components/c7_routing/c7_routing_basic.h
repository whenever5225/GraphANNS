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
#include "../../elements/nodes/params/param_include.h"

class C7RoutingBasic : public ComponentsBasic {
protected:
    static int InsertIntoPool(NeighborFlag *addr, unsigned K, const NeighborFlag& nn) {
        // find the location to insert
        int left = 0, right = K - 1;
        if (addr[left].distance_ > nn.distance_) {
            memmove((char *) &addr[left + 1], &addr[left], K * sizeof(NeighborFlag));
            addr[left] = nn;
            return left;
        }
        if (addr[right].distance_ < nn.distance_) {
            addr[K] = nn;
            return K;
        }
        while (left < right - 1) {
            int mid = (left + right) / 2;
            if (addr[mid].distance_ > nn.distance_) right = mid;
            else left = mid;
        }
        //check equal ID

        while (left > 0) {
            if (addr[left].distance_ < nn.distance_) break;
            if (addr[left].id_ == nn.id_) return K + 1;
            left--;
        }
        if (addr[left].id_ == nn.id_ || addr[right].id_ == nn.id_) return K + 1;
        memmove((char *) &addr[right + 1], &addr[right], (K - right) * sizeof(NeighborFlag));
        addr[right] = nn;
        return right;
    }

protected:
    unsigned search_L_; // candidate pool size for search
    unsigned K_;    // top-k for search
    VecValType *query_ = nullptr;    // query data
    unsigned query_id_; // current query id
    std::vector<unsigned> res_; // current query result
};

#endif //GRAPHANNS_C7_ROUTING_BASIC_H
