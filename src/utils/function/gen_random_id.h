/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: gen_random_id.h
@Time: 2022/4/1 8:00 PM
@Desc:
***************************/

#ifndef GRAPHANNS_GEN_RANDOM_ID_H
#define GRAPHANNS_GEN_RANDOM_ID_H

#include <random>

/**
 * generate random id number
 * @param id
 * @param num 是总个数
 * @param size 生成的n个数，范围在 [0,num) 之间。不重复
 */

template<typename TID = IDType, typename TSize = unsigned>
void GenRandomID(TID *id, TID num, TSize size) {
    std::mt19937 rng(random());
    for (TSize i = 0; i < size; ++i) {
        id[i] = rng() % (num - size);
    }
    std::sort(id, id + size);

    for (TSize i = 1; i < size; ++i) {
        if (id[i] <= id[i - 1]) {
            id[i] = id[i - 1] + 1;
        }
    }
    TID off = rng() % num;
    for (TSize i = 0; i < size; ++i) {
        id[i] = (id[i] + off) % num;
    }
}

#endif //GRAPHANNS_GEN_RANDOM_ID_H
