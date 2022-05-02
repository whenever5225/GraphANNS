/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: meta_data.h
@Time: 2022/5/2 11:18
@Desc: 
***************************/

#ifndef GRAPHANNS_META_DATA_H
#define GRAPHANNS_META_DATA_H

#include "../data_objects_define.h"

template<typename T = VecValType>
struct MetaData {
    T *data = nullptr;
    unsigned num = 0;
    unsigned dim = 0;
    std::string file_path;

    CStatus load(const std::string& path) {
        std::ifstream in(path.data(), std::ios::binary);
        if (!in.is_open()) {
            return CStatus(path + " open file error!");
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
        file_path = path;
        return CStatus();
    }

    virtual ~MetaData() {
        if (data) {
            delete[] data;
            data = nullptr;
        }
    }
};

#endif //GRAPHANNS_META_DATA_H
