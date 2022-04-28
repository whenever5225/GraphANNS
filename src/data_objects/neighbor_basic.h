/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: neighbor.h
@Time: 2022/4/12 11:13 AM
@Desc: simple neighbor with <id> and <distances> information
***************************/

#ifndef GRAPHANNS_NEIGHBOR_H
#define GRAPHANNS_NEIGHBOR_H

#include "../utils/utils_define.h"

struct Neighbor {
public:
    Neighbor() = default;

    Neighbor(unsigned id, DistResType distance) : id_{id}, distance_{distance} {}

    inline bool operator<(const Neighbor &other) const {
        return distance_ < other.distance_;
    }
    inline bool operator>(const Neighbor &other) const {
        return distance_ > other.distance_;
    }

public:
    unsigned id_;
    DistResType distance_;
};

#endif //GRAPHANNS_NEIGHBOR_H
