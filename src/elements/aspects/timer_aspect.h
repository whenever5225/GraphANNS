/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: timer_aspect.h
@Time: 2022/10/25 11:19 PM
@Desc:  statistic run time
***************************/

#ifndef GRAPHANNS_TIMER_ASPECT_H
#define GRAPHANNS_TIMER_ASPECT_H

#include <chrono>
#include "../elements_define.h"

class TimerAspect : public CGraph::GAspect {
public:
    /**
     * record time cost of run function
     */
    CStatus beginRun() override {
        start_ts_ = std::chrono::high_resolution_clock::now();
        return CStatus();
    }

    CVoid finishRun(const CStatus& curStatus) override {
        std::chrono::duration<double, std::milli> span = std::chrono::high_resolution_clock::now() - start_ts_;
        printf("[TIME] %s time cost is : %0.2lf ms\n",
                            this->getName().c_str(), span.count());
    }

private:
    std::chrono::high_resolution_clock::time_point start_ts_;
};

#endif //GRAPHANNS_TIMER_ASPECT_H
