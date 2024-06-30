/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: S-MABG.cpp
@Time: 2022/10/31 10:01 PM
@Desc: Multichannel Aggregation By Graph
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
    std::cout << "[PARAM] Modal1 index path: " << argv[argv_count++] << std::endl;      // 6
    std::cout << "[PARAM] Modal2 index path: " << argv[argv_count++] << std::endl;      // 7
    std::cout << "[PARAM] Save Result path: " << argv[argv_count++] << std::endl;       // 8
    std::cout << "[PARAM] thread number: " << argv[argv_count++] << std::endl;          // 9
    std::cout << "[PARAM] Modal1 distance weight: " << argv[argv_count++] << std::endl; // 10
    std::cout << "[PARAM] Modal2 distance weight: " << argv[argv_count++] << std::endl; // 11
    std::cout << "[PARAM] top-k: " << argv[argv_count++] << std::endl;                  // 12
    std::cout << "[PARAM] gt-k: " << argv[argv_count++] << std::endl;                   // 13
    std::cout << "[PARAM] L_search: " << argv[argv_count++] << std::endl;               // 14
    std::cout << "[PARAM] is norm for modal1?: " << argv[argv_count++] << std::endl;    // 15
    std::cout << "[PARAM] is norm for modal2?: " << argv[argv_count++] << std::endl;    // 16
    std::cout << "[PARAM] is skip number for modal2?: " << argv[argv_count++] << std::endl;    // 17
    std::cout << "[PARAM] skip number for modal2?: " << argv[argv_count++] << std::endl;    // 18
    std::cout << "[PARAM] is multi-results equal?: " << argv[argv_count++] << std::endl;    // 19
    std::cout << "[PARAM] is delete id?: " << argv[argv_count++] << std::endl;              // 20
    std::cout << "[PARAM] Delete id path: " << argv[argv_count++] << std::endl;             // 21
    std::cout << "[PARAM] Single channel candidate top-k size: " << argv[argv_count++] << std::endl;         // 22
    unsigned top_k = strtoul(argv[12], nullptr, 10);
    unsigned gtk = strtoul(argv[13], nullptr, 10);
    unsigned l = strtoul(argv[14], nullptr, 10);
    Params.set_search_param(argv[1], argv[2], argv[3],
                            argv[4], argv[5], argv[8], top_k, gtk,
                            l, argv[6]);
    unsigned thread_num = strtoul(argv[9], nullptr, 10);
    unsigned is_norm_modal1 = strtoul(argv[15], nullptr, 10);
    unsigned is_norm_modal2 = strtoul(argv[16], nullptr, 10);
    unsigned is_skip = strtoul(argv[17], nullptr, 10);
    unsigned skip_num = strtoul(argv[18], nullptr, 10);
    unsigned is_multiple_res_equal = strtoul(argv[19], nullptr, 10);
    unsigned is_delete_id = strtoul(argv[20], nullptr, 10);
    unsigned candi_top_k = strtoul(argv[19], nullptr, 10);
    Params.set_general_param(thread_num, is_norm_modal1, is_norm_modal2, is_skip, skip_num,
                             is_multiple_res_equal, is_delete_id);
    Params.set_candidate_top_k(candi_top_k);
    float w1 = strtof(argv[10], nullptr);
    float w2 = strtof(argv[11], nullptr);
    Params.set_data_param(w1, w2);
    Params.set_modal_index_path(argv[6], argv[7]);

    if (is_delete_id) {
        Params.set_delete_id_path(argv[21]);
    }

    GPipelinePtr pipeline = GPipelineFactory::create();

    GElementPtr a, b, c, d, e, f, g, h, i, j, ef_cluster = nullptr, gh_cluster = nullptr;
    // configuration
    CStatus status = pipeline->registerGElement<ConfigAlgNPGNode>(&a, {}, "config_npg");
    status += pipeline->registerGElement<ConfigModelNode>(&b, {a}, "config_model");
    status += pipeline->registerGElement<LoadModal1IndexNode>(&c, {a, b}, "load_modal1_index");
    status += pipeline->registerGElement<LoadModal2IndexNode>(&d, {a, b}, "load_modal1_index");

    //modal1 search
    e = pipeline->createGNode<C6SeedKGraphModal1>(GNodeInfo("c6_random_modal1"));
    f = pipeline->createGNode<C7RoutingKGraphModal1>(GNodeInfo("c7_greedy_modal1"));

    ef_cluster = pipeline->createGGroup<SearchClusterModal1>({e, f});
    status += pipeline->registerGElement<SearchClusterModal1>(&ef_cluster, {c}, "search_modal1");

    //modal2 search
    g = pipeline->createGNode<C6SeedKGraphModal2>(GNodeInfo("c6_random_modal2"));
    h = pipeline->createGNode<C7RoutingKGraphModal2>(GNodeInfo("c7_greedy_modal2"));

    gh_cluster = pipeline->createGGroup<SearchClusterModal2>({g, h});
    status += pipeline->registerGElement<SearchClusterModal2>(&gh_cluster, {d}, "search_modal2");

    status += pipeline->registerGElement<EvaMergeNode>(&i, {ef_cluster, gh_cluster}, "eva_merge");
    status += pipeline->registerGElement<EvaRecallNode>(&j, {i}, "eva_recall");

//    std::string result_path(argv[7]);
//    if (result_path != " ") {
//        status += pipeline->registerGElement<SaveResultNode>(&p, {i}, "save_result");
//    }
    a->setLevel(-1);
    b->setLevel(-2);

    ef_cluster->addGAspect<TimerAspect>()->addGAspect<TraceAspect>();
    gh_cluster->addGAspect<TimerAspect>()->addGAspect<TraceAspect>();
    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);

    return 0;
}



