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

    GElementPtr a, b, c, d, e, f = nullptr;
    // build
    CStatus status = pipeline->registerGElement<ConfigAlgNPGNode, -1>(&a, {}, "config_npg");
    status += pipeline->registerGElement<ConfigModelNode, -2>(&b, {a}, "config_model");
    status += pipeline->registerGElement<C1InitializationKGraph>(&c, {b}, "c1_nssg");

    status += pipeline->registerGElement<C2CandidateNSSGV1>(&d, {c}, "c2_nssg");
    status += pipeline->registerGElement<C3NeighborNSGV1>(&e, {d}, "c3_nsg");
    status += pipeline->registerGElement<SaveIndexNode>(&f, {e}, "save_index");

    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);
    return 0;
}
