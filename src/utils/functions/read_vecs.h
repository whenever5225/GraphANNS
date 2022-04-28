/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: read_vecs.h
@Time: 2022/4/7 8:04 PM
@Desc:
***************************/

#ifndef GRAPHANNS_READ_VECS_H
#define GRAPHANNS_READ_VECS_H

#include <fstream>
#include "../../../../CGraph/src/CGraph.h"

/**
 * load data in format 'fvecs' or 'ivecs'
 * @tparam T
 * @param filename
 * @param data
 * @param num
 * @param dim
 */

// todo : suggest, this function must be refine.
template<typename T>
CStatus read_vecs(char *filename, T *&data, unsigned &num, unsigned &dim) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        return CStatus("open file error!");
    }
    in.read((char *) &dim, 4);
    in.seekg(0, std::ios::end);
    std::ios::pos_type ss = in.tellg();
    auto f_size = (size_t) ss;
    num = (unsigned) (f_size / (dim + 1) / 4);
    data = new T[num * dim];

    in.seekg(0, std::ios::beg);
    for (size_t i = 0; i < num; i++) {
        in.seekg(4, std::ios::cur);
        in.read((char *) (data + i * dim), dim * sizeof(T));
    }
    in.close();

    return CStatus();
}

#endif //GRAPHANNS_READ_VECS_H
