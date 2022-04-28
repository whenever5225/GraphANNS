/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: search_pool.h
@Time: 2022/4/14 10:04 PM
@Desc: candidate results when searching
***************************/

#ifndef GRAPHANNS_SEARCH_POOL_H
#define GRAPHANNS_SEARCH_POOL_H

struct SearchPool {
    unsigned id;
    DistResType distance;
    bool flag;

    SearchPool() = default;

    SearchPool(unsigned id, DistResType distance, bool f) : id{id}, distance{distance}, flag(f) {}

    inline bool operator<(const SearchPool &other) const {
        return distance < other.distance;
    }

    inline bool operator>(const SearchPool &other) const {
        return distance > other.distance;
    }
};

#endif //GRAPHANNS_SEARCH_POOL_H
