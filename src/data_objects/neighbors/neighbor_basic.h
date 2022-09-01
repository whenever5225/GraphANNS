/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: neighbor.h
@Time: 2022/4/12 11:13 AM
@Desc: simple neighbor with <id> and <distances> information
***************************/

#ifndef GRAPHANNS_NEIGHBOR_H
#define GRAPHANNS_NEIGHBOR_H

#include "../distances/distances_include.h"
#include "../data_objects_define.h"

struct Neighbor {
public:
    explicit Neighbor() : id_(-1), distance_(0) {}
    explicit Neighbor(unsigned id, DistResType distance) : id_{id}, distance_{distance} {}

    inline bool operator<(const Neighbor &other) const {
        return distance_ < other.distance_;
    }

    inline bool operator>(const Neighbor &other) const {
        return distance_ > other.distance_;
    }

public:
    IDType id_;
    DistResType distance_;
};

#endif //GRAPHANNS_NEIGHBOR_H
