/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: T-siftsmall.cpp
@Time: 2022/4/30 17:24
@Desc: 
***************************/

#include "../src/graph_anns.h"

using namespace CGraph;

int main() {
    GPipelinePtr pipeline = GPipelineFactory::create();

    GElementPtr a, b, c, d, e = nullptr;
    // build
    CStatus status = pipeline->registerGElement<ConfigNPG>(&a, {}, "config_npg");
    status += pipeline->registerGElement<C1InitializationKGraph>(&b, {a}, "c1_nssg");

    status += pipeline->registerGElement<C2CandidateNSSGV1>(&c, {b}, "c2_nssg");
    status += pipeline->registerGElement<C3NeighborNSGV1>(&d, {c}, "c3_nsg");
    status += pipeline->registerGElement<SaveIndex>(&e, {d}, "save_index");

    pipeline->createGParam<ParamNPG>(GRAPH_INFO_PARAM_KEY);     // pipeline执行之前，先构建 ParamNPG 参数

    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);
    return 0;
}