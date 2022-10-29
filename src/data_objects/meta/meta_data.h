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

template<typename T = float>
struct MetaData {
    T *data = nullptr;
    IDType num = 0;
    unsigned dim = 0;
    std::string file_path;

    CStatus norm(T *vec, const unsigned n, const unsigned d) {
        for (unsigned i = 0; i < n; i++) {
            float vector_norm = 0;
            for (unsigned j = 0; j < d; j++) {
                vector_norm += vec[i * d + j] * vec[i * d + j];
            }
            vector_norm = std::sqrt(vector_norm);
            for (unsigned j = 0; j < d; j++) {
                vec[i * d + j] /= vector_norm;
            }
        }
        return CStatus();
    }

    CStatus load(const std::string& path, const unsigned is_norm) {
        std::ifstream in(path.data(), std::ios::binary);
        if (!in.is_open()) {
            return CStatus(path + " open file error!");
        }
        unsigned dim_val_size = sizeof(unsigned);
        in.read((char *) &dim, dim_val_size);
        in.seekg(0, std::ios::end);
        std::ios::pos_type ss = in.tellg();
        auto f_size = (size_t) ss;
        num = (IDType) (f_size / (dim * sizeof(T) + dim_val_size));
        data = new T[num * dim];

        in.seekg(0, std::ios::beg);
        for (IDType i = 0; i < num; i++) {
            in.seekg(dim_val_size, std::ios::cur);
            in.read((char *) (data + i * dim), dim * sizeof(T));
        }
        in.close();
        file_path = path;
        if (is_norm) {
            norm(data, num, dim);
            printf("[EXEC] normalize vector complete!\n");
        }
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
