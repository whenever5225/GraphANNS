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
    std::cout << "[PARAM] Save Result path: " << argv[argv_count++] << std::endl;       // 6
    std::cout << "[PARAM] thread number: " << argv[argv_count++] << std::endl;          // 7
    std::cout << "[PARAM] Modal1 distance weight: " << argv[argv_count++] << std::endl; // 8
    std::cout << "[PARAM] Modal2 distance weight: " << argv[argv_count++] << std::endl; // 9
    std::cout << "[PARAM] top-k: " << argv[argv_count++] << std::endl;                  // 10
    std::cout << "[PARAM] gt-k: " << argv[argv_count++] << std::endl;                   // 11
    std::cout << "[PARAM] is norm for modal1?: " << argv[argv_count++] << std::endl;    // 12
    std::cout << "[PARAM] is norm for modal2?: " << argv[argv_count++] << std::endl;    // 13
    std::cout << "[PARAM] is skip number for modal2?: " << argv[argv_count++] << std::endl;    // 14
    std::cout << "[PARAM] skip number for modal2?: " << argv[argv_count++] << std::endl;// 15
    std::cout << "[PARAM] is multi-results equal?: " << argv[argv_count++] << std::endl;// 16
    unsigned topk = strtoul(argv[10], nullptr, 10);
    unsigned gtk = strtoul(argv[11], nullptr, 10);
    Params.set_search_param(argv[1], argv[2], argv[3],
                            argv[4], argv[5], argv[6], topk, gtk,
                            0, nullptr);
    unsigned thread_num = strtoul(argv[7], nullptr, 10);
    unsigned is_norm_modal1 = strtoul(argv[12], nullptr, 10);
    unsigned is_norm_modal2 = strtoul(argv[13], nullptr, 10);
    unsigned is_skip = strtoul(argv[14], nullptr, 10);
    unsigned skip_num = strtoul(argv[15], nullptr, 10);
    unsigned is_multiple_res_equal = strtoul(argv[16], nullptr, 10);
    Params.set_general_param(thread_num, is_norm_modal1, is_norm_modal2, is_skip, skip_num,
                             is_multiple_res_equal);
    float w1 = strtof(argv[8], nullptr);
    float w2 = strtof(argv[9], nullptr);
    Params.set_data_param(w1, w2);
    GPipelinePtr pipeline = GPipelineFactory::create();

    GElementPtr a, b, f, h, g;
    CStatus status = pipeline->registerGElement<ConfigAlgBruteForceNode, -1>(&a, {}, "config_brute_force");
    status += pipeline->registerGElement<ConfigModelNode, -2>(&b, {a}, "config_model");
    status += pipeline->registerGElement<EvaBruteForceNode>(&f, {a}, "eva_brute_force");
    status += pipeline->registerGElement<EvaRecallNode>(&h, {f}, "eva_recall");

    std::string result_path(argv[6]);
    if (result_path != " ") {
        status += pipeline->registerGElement<SaveResultNode>(&g, {f}, "save_result");
    }

    f->addGAspect<TimerAspect>()->addGAspect<TraceAspect>();
    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);
    return 0;
}
