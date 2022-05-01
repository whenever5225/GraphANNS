/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: param_basic_v2.h
@Time: 2022/4/30 17:51
@Desc: 
***************************/

#ifndef GRAPHANNS_PARAM_BASIC_V2_H
#define GRAPHANNS_PARAM_BASIC_V2_H

#include <string>

#include "../../../utils/utils.h"
#include "../../../data_objects/data_objects.h"
#include "../../CGraph/src/CGraph.h"
#include "../../../graph_anns_define.h"

template<typename T = VecValType>
struct ParamBasicV2 : public CGraph::GParam {
    T *data = nullptr;
    unsigned num = 0;
    unsigned dim = 0;

    CVoid reset() override {
        /**
         * todo 要看一下，这个pipeline结束之后，是否需要 reset啥东西
         */
    }

    CStatus load(const std::string& path) override {
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
        return CStatus();
    }

    ~ParamBasicV2() override {
        CGRAPH_DELETE_PTR(data)
    }
};

#endif //GRAPHANNS_PARAM_BASIC_V2_H
