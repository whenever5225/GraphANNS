/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: simple_neighbor.h
@Time: 2022/4/12 11:13 AM
@Desc: simple neighbor with <id> and <distances> information
***************************/

#ifndef GRAPHANNS_SIMPLE_NEIGHBOR_H
#define GRAPHANNS_SIMPLE_NEIGHBOR_H

#include "../utils_proxy.h"

struct SimpleNeighbor {
    unsigned id_;
    DistResType distance_;

    SimpleNeighbor() = default;

    SimpleNeighbor(unsigned id, DistResType distance) : id_{id}, distance_{distance} {}

    inline bool operator<(const SimpleNeighbor &other) const {
        return distance_ < other.distance_;
    }
};

#endif //GRAPHANNS_SIMPLE_NEIGHBOR_H
