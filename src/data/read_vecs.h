/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: read_vecs.h
@Time: 2022/4/7 8:04 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_READ_VECS_H
#define GRAPHANNS_READ_VECS_H
#include <fstream>

/**
 * load data in format 'fvecs' or 'ivec'
 * @tparam T
 * @param filename
 * @param data
 * @param num
 * @param dim
 */

template<typename T>
void read_vecs(char *filename, T *&data, unsigned &num, unsigned &dim) {
    std::ifstream in(filename, std::ios::binary);
    if (!in.is_open()) {
        printf("open file error!\n");
        exit(-1);
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
}
#endif //GRAPHANNS_READ_VECS_H
