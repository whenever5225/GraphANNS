/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: S-MABB.cpp
@Time: 2022/11/1 8:32 PM
@Desc: Multichannel aggregation by brute force
***************************/

#include <cstdlib>
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
    std::cout << "[PARAM] is delete id?: " << argv[argv_count++] << std::endl;          // 17
    std::cout << "[PARAM] Delete id path: " << argv[argv_count++] << std::endl;         // 18
    std::cout << "[PARAM] Single channel candidate top-k size: " << argv[argv_count++] << std::endl;         // 19
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
    unsigned is_delete_id = strtoul(argv[17], nullptr, 10);
    unsigned candi_top_k = strtoul(argv[19], nullptr, 10);
    Params.set_general_param(thread_num, is_norm_modal1, is_norm_modal2, is_skip, skip_num,
                             is_multiple_res_equal, is_delete_id);
    Params.set_candidate_top_k(candi_top_k);
    float w1 = strtof(argv[8], nullptr);
    float w2 = strtof(argv[9], nullptr);
    Params.set_data_param(w1, w2);

    if (is_delete_id) {
        Params.set_delete_id_path(argv[18]);
    }
    GPipelinePtr pipeline = GPipelineFactory::create();

    GElementPtr a, b, c, d, f, h, g;
    CStatus status = pipeline->registerGElement<ConfigAlgBruteForceNode>(&a, {}, "config_brute_force");
    status += pipeline->registerGElement<ConfigModelNode>(&b, {a}, "config_model");
    status += pipeline->registerGElement<EvaModal1BruteForceNode<BiDistanceCalculator<DistInnerProduct, DistAttributeSimilarity>
    >>(&f, {a, b}, "eva_modal1_brute_force");
    status += pipeline->registerGElement<EvaModal2BruteForceNode<BiDistanceCalculator<DistInnerProduct, DistAttributeSimilarity>
    >>(&c, {a, b}, "eva_modal2_brute_force");
    status += pipeline->registerGElement<EvaMergeNode>(&d, {c, f}, "eva_merge");
    status += pipeline->registerGElement<EvaRecallNode>(&h, {d}, "eva_recall");

    std::string result_path(argv[6]);
    if (result_path != " ") {
        status += pipeline->registerGElement<SaveResultNode>(&g, {d}, "save_result");
    }

    f->addGAspect<TimerAspect>()->addGAspect<TraceAspect>();
    c->addGAspect<TimerAspect>()->addGAspect<TraceAspect>();

    a->setLevel(-1);
    b->setLevel(-2);
    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);
    return 0;
}
