/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: insert_into_pool.h
@Time: 2022/4/8 11:30 AM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_INSERT_INTO_POOL_H
#define GRAPHANNS_INSERT_INTO_POOL_H

#include "../../../params/search_params.h"

/**
 * insert the element 'nn' into search pool
 * @param addr
 * @param K
 * @param nn
 * @return
 */

int InsertIntoPool(SearchParams::search_pool *addr, unsigned K, SearchParams::search_pool nn) {
    // find the location to insert
    int left = 0, right = K - 1;
    if (addr[left].distance > nn.distance) {
        memmove((char *) &addr[left + 1], &addr[left], K * sizeof(SearchParams::search_pool));
        addr[left] = nn;
        return left;
    }
    if (addr[right].distance < nn.distance) {
        addr[K] = nn;
        return K;
    }
    while (left < right - 1) {
        int mid = (left + right) / 2;
        if (addr[mid].distance > nn.distance)right = mid;
        else left = mid;
    }
    //check equal ID

    while (left > 0) {
        if (addr[left].distance < nn.distance) break;
        if (addr[left].id == nn.id) return K + 1;
        left--;
    }
    if (addr[left].id == nn.id || addr[right].id == nn.id)return K + 1;
    memmove((char *) &addr[right + 1], &addr[right], (K - right) * sizeof(SearchParams::search_pool));
    addr[right] = nn;
    return right;
}

#endif //GRAPHANNS_INSERT_INTO_POOL_H
