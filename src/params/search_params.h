/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: search_params.h
@Time: 2022/4/7 9:00 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_SEARCH_PARAMS_H
#define GRAPHANNS_SEARCH_PARAMS_H

#include "../../CGraph/src/CGraph.h"

/**
 * parameters for search
 */

class SearchParams : public CGraph::GParam {
public:
    unsigned top_k = 20;
    unsigned search_L = top_k + 500;
    unsigned query = 0;

    struct search_pool {
        unsigned id;
        float distance;
        bool flag;

        search_pool() = default;

        search_pool(unsigned id, float distance, bool f) : id{id}, distance{distance}, flag(f) {}

        inline bool operator<(const search_pool &other) const {
            return distance < other.distance;
        }

        inline bool operator>(const search_pool &other) const {
            return distance > other.distance;
        }
    };

    std::vector<search_pool> sp;
    std::vector<std::vector<unsigned> > results;

    CVoid reset() override {
        sp.clear();
    }

};

#endif //GRAPHANNS_SEARCH_PARAMS_H
