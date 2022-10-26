/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: S-siftsmall.cpp
@Time: 2022/4/30 17:25
@Desc:
***************************/

#include <cstdlib>
#include "src/graph_anns.h"

using namespace CGraph;
//using Param = ParamConfig;

int main(int argc, char **argv) {
    time_t tt = time(nullptr);
    tm* t=localtime(&tt);
    std::cout << std::endl;
    std::cout << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday
              << "-" << t->tm_hour << "-" << t->tm_min << "-" << t->tm_sec << std::endl;
    std::cout << std::endl;

    unsigned argv_count = 1;

    std::cout << "[PARAM] Modal1 base path: " << argv[argv_count++] << std::endl;       // 1
    std::cout << "[PARAM] Modal2 base path: " << argv[argv_count++] << std::endl;       // 2
    std::cout << "[PARAM] Modal1 query path: " << argv[argv_count++] << std::endl;      // 3
    std::cout << "[PARAM] Modal2 query path: " << argv[argv_count++] << std::endl;      // 4
    std::cout << "[PARAM] Groundtruth path: " << argv[argv_count++] << std::endl;       // 5
    std::cout << "[PARAM] thread number: " << argv[argv_count++] << std::endl;          // 6
    std::cout << "[PARAM] Modal1 distance weight: " << argv[argv_count++] << std::endl; // 7
    std::cout << "[PARAM] Modal2 distance weight: " << argv[argv_count++] << std::endl; // 8
    std::cout << "[PARAM] top-k: " << argv[argv_count++] << std::endl;                  // 9
    unsigned topk = strtoul(argv[9], nullptr, 10);
    Params.set_search_param(argv[1], argv[2], argv[3],
                            argv[4], argv[5], topk, 0, nullptr);
    unsigned thread_num = strtoul(argv[6], nullptr, 10);
    Params.set_general_param(thread_num);
    float w1 = strtof(argv[7], nullptr);
    float w2 = strtof(argv[8], nullptr);
    Params.set_data_param(w1, w2);
    GPipelinePtr pipeline = GPipelineFactory::create();

    GElementPtr a, b, f, h;
    CStatus status = pipeline->registerGElement<ConfigAlgBruteForceNode, -1>(&a, {}, "config_brute_force");
    status += pipeline->registerGElement<ConfigModelNode, -2>(&b, {a}, "config_model");
    status += pipeline->registerGElement<EvaBruteForceNode>(&f, {a}, "eva_brute_force");
    status += pipeline->registerGElement<EvaRecallNode>(&h, {f}, "eva_recall");

    f->addGAspect<TimerAspect>()->addGAspect<TraceAspect>();
    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);
    return 0;
}
