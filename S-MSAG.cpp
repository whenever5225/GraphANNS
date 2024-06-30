/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: S-siftsmall.cpp
@Time: 2022/4/30 17:25
@Desc: 
***************************/

#include "src/graph_anns.h"

using namespace CGraph;

int main(int argc, char **argv) {
    time_t tt = time(nullptr);
    tm* t=localtime(&tt);
    std::cout << std::endl;
    std::cout << t->tm_year + 1900 << "-" << t->tm_mon + 1 << "-" << t->tm_mday
              << "-" << t->tm_hour << "-" << t->tm_min << "-" << t->tm_sec << std::endl;
    std::cout << std::endl;

    unsigned argv_count = 0;

    std::cout << "[RUN] Execution object: " << argv[argv_count++] << std::endl;         // 0
    std::cout << "[PARAM] Modal1 base path: " << argv[argv_count++] << std::endl;       // 1
    std::cout << "[PARAM] Modal2 base path: " << argv[argv_count++] << std::endl;       // 2
    std::cout << "[PARAM] Modal1 query path: " << argv[argv_count++] << std::endl;      // 3
    std::cout << "[PARAM] Modal2 query path: " << argv[argv_count++] << std::endl;      // 4
    std::cout << "[PARAM] Groundtruth path: " << argv[argv_count++] << std::endl;       // 5
    std::cout << "[PARAM] Index path: " << argv[argv_count++] << std::endl;             // 6
    std::cout << "[PARAM] Save Result path: " << argv[argv_count++] << std::endl;       // 7
    std::cout << "[PARAM] thread number: " << argv[argv_count++] << std::endl;          // 8
    std::cout << "[PARAM] Modal1 distance weight: " << argv[argv_count++] << std::endl; // 9
    std::cout << "[PARAM] Modal2 distance weight: " << argv[argv_count++] << std::endl; // 10
    std::cout << "[PARAM] top-k: " << argv[argv_count++] << std::endl;                  // 11
    std::cout << "[PARAM] gt-k: " << argv[argv_count++] << std::endl;                   // 12
    std::cout << "[PARAM] L_search: " << argv[argv_count++] << std::endl;               // 13
    std::cout << "[PARAM] is norm for modal1?: " << argv[argv_count++] << std::endl;    // 14
    std::cout << "[PARAM] is norm for modal2?: " << argv[argv_count++] << std::endl;    // 15
    std::cout << "[PARAM] is skip number for modal2?: " << argv[argv_count++] << std::endl;    // 16
    std::cout << "[PARAM] skip number for modal2?: " << argv[argv_count++] << std::endl;    // 17
    std::cout << "[PARAM] is multi-results equal?: " << argv[argv_count++] << std::endl;    // 18
    std::cout << "[PARAM] is delete id?: " << argv[argv_count++] << std::endl;              // 19
    std::cout << "[PARAM] Delete id path: " << argv[argv_count++] << std::endl;             // 20
    unsigned top_k = strtoul(argv[11], nullptr, 10);
    unsigned gtk = strtoul(argv[12], nullptr, 10);
    unsigned l = strtoul(argv[13], nullptr, 10);
    Params.set_search_param(argv[1], argv[2], argv[3],
                            argv[4], argv[5], argv[7], top_k, gtk,
                            l, argv[6]);
    unsigned thread_num = strtoul(argv[8], nullptr, 10);
    unsigned is_norm_modal1 = strtoul(argv[14], nullptr, 10);
    unsigned is_norm_modal2 = strtoul(argv[15], nullptr, 10);
    unsigned is_skip = strtoul(argv[16], nullptr, 10);
    unsigned skip_num = strtoul(argv[17], nullptr, 10);
    unsigned is_multiple_res_equal = strtoul(argv[18], nullptr, 10);
    unsigned is_delete_id = strtoul(argv[19], nullptr, 10);
    Params.set_general_param(thread_num, is_norm_modal1, is_norm_modal2, is_skip, skip_num,
                             is_multiple_res_equal, is_delete_id);
    float w1 = strtof(argv[9], nullptr);
    float w2 = strtof(argv[10], nullptr);
    Params.set_data_param(w1, w2);

    if (is_delete_id) {
        Params.set_delete_id_path(argv[20]);
    }

    GPipelinePtr pipeline = GPipelineFactory::create();

    GElementPtr a, b, f, g, h, i, p, gh_region= nullptr;
    // build
    CStatus status = pipeline->registerGElement<ConfigAlgNPGNode>(&a, {}, "config_npg");
    status += pipeline->registerGElement<ConfigModelNode>(&b, {a}, "config_model");
    status += pipeline->registerGElement<LoadIndexNode>(&f, {a}, "load_index");

    //search
    g = pipeline->createGNode<C6SeedKGraph>(GNodeInfo("c6_random"));
    h = pipeline->createGNode<C7RoutingKGraph>(GNodeInfo("c7_greedy"));

    gh_region = pipeline->createGGroup<SearchRegion>({g, h});
    status += pipeline->registerGElement<SearchRegion>(&gh_region, {f}, "search");

    status += pipeline->registerGElement<EvaRecallNode>(&i, {gh_region}, "eva_recall");

//    std::string result_path(argv[7]);
//    if (result_path != " ") {
//        status += pipeline->registerGElement<SaveResultNode>(&p, {i}, "save_result");
//    }
    a->setLevel(-1);
    b->setLevel(-2);

    gh_region->addGAspect<TimerAspect>()->addGAspect<TraceAspect>();
    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);

    return 0;
}
