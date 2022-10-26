/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: trace_aspect.h
@Time: 2022/10/26 6:31 PM
@Desc: print exec complete
***************************/

#ifndef GRAPHANNS_TRACE_ASPECT_H
#define GRAPHANNS_TRACE_ASPECT_H

#include "../elements_define.h"

class TraceAspect : public CGraph::GAspect {
public:
    CStatus beginInit() override {
        printf("[EXEC] %s init begin ...\n", this->getName().c_str());
        return CStatus();
    }

    CVoid finishInit(const CStatus& curStatus) override {
        printf("[EXEC] %s init finished, error code is %d ...\n", this->getName().c_str(),
                            curStatus.getCode());
    }

    CStatus beginRun() override {
        printf("[EXEC] %s run begin ...\n", this->getName().c_str());
        return CStatus();
    }

    CVoid finishRun(const CStatus& curStatus) override {
        if (!curStatus.isOK()) {
            printf("[EXEC] %s run finished, status is ok ...\n", this->getName().c_str());
        } else {
            printf("[EXEC] %s run finished, error code is %d ...\n", this->getName().c_str(),
                                curStatus.getCode());
        }
    }

    CStatus beginDestroy() override {
        printf("[EXEC] %s destroy begin ...\n", this->getName().c_str());
        return CStatus();
    }

    CVoid finishDestroy(const CStatus& curStatus) override {
        printf("[EXEC] %s destroy finished, error code is %d ...\n", this->getName().c_str(),
                            curStatus.getCode());
    }
};

#endif //GRAPHANNS_TRACE_ASPECT_H
