/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: S-siftsmall.cpp
@Time: 2022/4/30 17:25
@Desc:
***************************/

#include "src/graph_anns.h"

using namespace CGraph;

int main() {
    GPipelinePtr pipeline = GPipelineFactory::create();

    GElementPtr a, b, f, g, h;
    // build
    CStatus status = pipeline->registerGElement<ConfigAlgBruteForceNode, -1>(&a, {}, "config_brute_force");
    status += pipeline->registerGElement<ConfigModelNode, -2>(&b, {a}, "config_model");
    status += pipeline->registerGElement<EvaBruteForceNode>(&f, {a}, "eva_brute_force");
//    status += pipeline->registerGElement<ConfigEvaNode>(&g, {f}, "config_eva");
    status += pipeline->registerGElement<EvaRecallNode>(&h, {f}, "eva_recall");

    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);
    return 0;
}
