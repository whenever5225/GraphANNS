/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: graph_params.h
@Time: 2022/3/30 3:40 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_GRAPH_PARAMS_H
#define GRAPHANNS_GRAPH_PARAMS_H

#include "../CGraph/src/CGraph.h"
/**
 * common parameters of graph index
 */
class graph_params : public CGraph::GParam {
public:
    unsigned out_degree = 20;
    std::string index_path = "/Users/wmz/Documents/Postgraduate/Code/tmp/test.index";

    struct simple_neighbor {
        unsigned id;
        float distance;

        simple_neighbor() = default;

        simple_neighbor(unsigned id, float distance) : id{id}, distance{distance} {}

        inline bool operator<(const simple_neighbor &other) const {
            return distance < other.distance;
        }
    };

    typedef std::vector<std::vector<simple_neighbor> > graph_neighbor;
    typedef std::vector<std::vector<unsigned> > graph_matrix;

    graph_neighbor graph_n;
    graph_matrix graph_m;

    CVoid reset()override{

    }
};

#endif //GRAPHANNS_GRAPH_PARAMS_H
