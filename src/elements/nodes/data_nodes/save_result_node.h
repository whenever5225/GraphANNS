/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: save_result_node.h
@Time: 2022/10/27 7:03 PM
@Desc: save search result
***************************/

#ifndef GRAPHANNS_SAVE_RESULT_NODE_H
#define GRAPHANNS_SAVE_RESULT_NODE_H

#include <fstream>

#include "../../../../CGraph/src/CGraph.h"
#include "../../elements_define.h"

class SaveResultNode : public CGraph::GNode {
public:
    CStatus run() override {
        CGRAPH_EMPTY_FUNCTION
    }

    CStatus destroy() override {
        auto *s_param = CGRAPH_GET_GPARAM(AlgParamBasic, GA_ALG_PARAM_BASIC_KEY);
        CGRAPH_ASSERT_NOT_NULL(s_param)

        std::ofstream f_out(Params.GA_ALG_RESULT_PATH_);
        for (auto & result : s_param->results) {
            int GK = (int) result.size();
            for (int j = 0; j < GK; j++) {
                f_out << result[j];
                j == (GK - 1) ? f_out << "\n" : f_out << " ";
            }
        }
        f_out.close();
        return CStatus();
    }
};

#endif //GRAPHANNS_SAVE_RESULT_NODE_H
