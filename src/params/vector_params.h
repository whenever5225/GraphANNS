/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: vector_params.h
@Time: 2022/3/28 9:01 PM
@Desc: TODO
***************************/

#ifndef GRAPHANNS_VECTOR_PARAMS_H
#define GRAPHANNS_VECTOR_PARAMS_H
#include "../../CGraph/src/CGraph.h"

/**
 * parameters of vector
 */

class vector_params : public CGraph::GParam{
public:
    /**
     * load vector
     */
    std::string base_path;
    float *data;
    unsigned num;
    unsigned dim;

    /**
     * load query
     * @return
     */
     std::string query_path;
     float *query;
     unsigned q_num;
     unsigned q_dim;

     /**
      * load groundtruth
      * @return
      */
      std::string groundtruth_path;
      unsigned *gt;
      unsigned gt_num;
      unsigned gt_dim;

    CVoid reset()override{

    }

};
#endif //GRAPHANNS_VECTOR_PARAMS_H
