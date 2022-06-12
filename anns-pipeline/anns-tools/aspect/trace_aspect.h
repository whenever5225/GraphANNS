/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: trace_aspect.h
@Time: 2022/6/12 15:22
@Desc: 
***************************/

#ifndef GRAPHANNS_TRACE_ASPECT_H
#define GRAPHANNS_TRACE_ASPECT_H

#include "../../../CGraph/src/CGraph.h"

class TraceAspect : public CGraph::GAspect {
public:
    CStatus beginRun() override {
        CGraph::CGRAPH_ECHO(" ----> [%s] node begin to run ...",
                            this->getName().c_str());
        return CStatus();
    }

    CVoid finishRun(const CStatus& curStatus) override {
        CGraph::CGRAPH_ECHO(" ----> [%s] node run finish, status code is [%d] ...",
                            this->getName().c_str(), curStatus.getCode());
    }
};

#endif //GRAPHANNS_TRACE_ASPECT_H
