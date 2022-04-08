/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: gen_random_id.h
@Time: 2022/4/1 8:00 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_GEN_RANDOM_ID_H
#define GRAPHANNS_GEN_RANDOM_ID_H
#include <random>

/**
 * generate random id number
 * @param id
 * @param num
 * @param size
 */

void GenRandomID(unsigned *id, unsigned num, unsigned size) {
    std::mt19937 rng(rand());
    for (unsigned i = 0; i < size; ++i) {
        id[i] = rng() % (num - size);
    }
    std::sort(id, id + size);

    for (unsigned i = 1; i < size; ++i) {
        if (id[i] <= id[i - 1]) {
            id[i] = id[i - 1] + 1;
        }
    }
    unsigned off = rng() % num;
    for (unsigned i = 0; i < size; ++i) {
        id[i] = (id[i] + off) % num;
    }
}
#endif //GRAPHANNS_GEN_RANDOM_ID_H
