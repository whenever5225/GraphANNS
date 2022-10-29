/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: T-siftsmall.cpp
@Time: 2022/4/30 17:24
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

    unsigned argv_count = 1;

    std::cout << "[PARAM] Modal1 base path: " << argv[argv_count++] << std::endl;       // 1
    std::cout << "[PARAM] Modal2 base path: " << argv[argv_count++] << std::endl;       // 2
    std::cout << "[PARAM] Index path: " << argv[argv_count++] << std::endl;             // 3
    std::cout << "[PARAM] thread number: " << argv[argv_count++] << std::endl;          // 4
    std::cout << "[PARAM] Modal1 distance weight: " << argv[argv_count++] << std::endl; // 5
    std::cout << "[PARAM] Modal2 distance weight: " << argv[argv_count++] << std::endl; // 6
    std::cout << "[PARAM] L_candidate: " << argv[argv_count++] << std::endl;            // 7
    std::cout << "[PARAM] R_neighbor: " << argv[argv_count++] << std::endl;             // 8
    std::cout << "[PARAM] C_neighbor: " << argv[argv_count++] << std::endl;             // 9
    std::cout << "[PARAM] k_init_graph: " << argv[argv_count++] << std::endl;           // 10
    std::cout << "[PARAM] nn_size: " << argv[argv_count++] << std::endl;                // 11
    std::cout << "[PARAM] rnn_size: " << argv[argv_count++] << std::endl;               // 12
    std::cout << "[PARAM] pool_size: " << argv[argv_count++] << std::endl;              // 13
    std::cout << "[PARAM] iter time: " << argv[argv_count++] << std::endl;              // 14
    std::cout << "[PARAM] sample number: " << argv[argv_count++] << std::endl;          // 15
    std::cout << "[PARAM] graph quality threshold: " << argv[argv_count++] << std::endl;// 16
    std::cout << "[PARAM] is norm for modal1?: " << argv[argv_count++] << std::endl;    // 17
    std::cout << "[PARAM] is norm for modal2?: " << argv[argv_count++] << std::endl;    // 18
    std::cout << "[PARAM] is skip number for modal2?: " << argv[argv_count++] << std::endl;    // 19
    std::cout << "[PARAM] skip number for modal2?: " << argv[argv_count++] << std::endl;    // 20
    unsigned thread_num = strtoul(argv[4], nullptr, 10);
    unsigned is_norm_modal1 = strtoul(argv[17], nullptr, 10);
    unsigned is_norm_modal2 = strtoul(argv[18], nullptr, 10);
    unsigned is_skip = strtoul(argv[19], nullptr, 10);
    unsigned skip_num = strtoul(argv[20], nullptr, 10);
    Params.set_general_param(thread_num, is_norm_modal1, is_norm_modal2, is_skip, skip_num);
    float w1 = strtof(argv[5], nullptr);
    float w2 = strtof(argv[6], nullptr);
    Params.set_data_param(w1, w2);
    unsigned L_candidate = strtoul(argv[7], nullptr, 10);
    unsigned R_neighbor = strtoul(argv[8], nullptr, 10);
    unsigned C_neighbor = strtoul(argv[9], nullptr, 10);
    unsigned k_init_graph = strtoul(argv[10], nullptr, 10);
    unsigned nn_size = strtoul(argv[11], nullptr, 10);
    unsigned rnn_size = strtoul(argv[12], nullptr, 10);
    unsigned pool_size = strtoul(argv[13], nullptr, 10);
    unsigned iter = strtoul(argv[14], nullptr, 10);
    unsigned sample_num = strtoul(argv[15], nullptr, 10);
    float threshold = strtof(argv[16], nullptr);
    Params.set_train_param(argv[1], argv[2], argv[3],
                           L_candidate, R_neighbor, C_neighbor, k_init_graph, nn_size, rnn_size, pool_size,
                           iter, sample_num, threshold);

    GPipelinePtr pipeline = GPipelineFactory::create();
    GElementPtr a, b, c, d, e, cde_region, f = nullptr;

    // build
    CStatus status = pipeline->registerGElement<ConfigAlgNPGNode, -1>(&a, {}, "config_npg");
    status += pipeline->registerGElement<ConfigModelNode, -2>(&b, {a}, "config_model");

    c = pipeline->createGNode<C1InitializationNNDescent>(GNodeInfo("c1_nssg"));
    d = pipeline->createGNode<C2CandidateNSSGV1>(GNodeInfo("c2_nssg"));
    e = pipeline->createGNode<C3NeighborNSGV1>(GNodeInfo("c3_nsg"));

    cde_region = pipeline->createGGroup<GCluster>({c, d, e});

    status += pipeline->registerGElement<GCluster>(&cde_region, {b}, "build");
    status += pipeline->registerGElement<SaveIndexNode>(&f, {cde_region}, "save_index");

    pipeline->addGAspect<TimerAspect>()->addGAspect<TraceAspect>();

    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);
    return 0;
}
