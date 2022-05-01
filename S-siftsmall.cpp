/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: S-siftsmall.cpp
@Time: 2022/4/30 17:25
@Desc: 
***************************/

#include "../src/graph_anns.h"

using namespace CGraph;

int main() {
    GPipelinePtr pipeline = GPipelineFactory::create();

    GElementPtr a, f, g, h, i, gh_region= nullptr;
    // build
    CStatus status = pipeline->registerGElement<ConfigAlgNPGNode, -1>(&a, {}, "config_npg");
    status += pipeline->registerGElement<LoadIndexNode>(&f, {a}, "load_index");

    //search
    g = pipeline->createGNode<C6SeedKGraph>(GNodeInfo({}, "c6_random"));
    h = pipeline->createGNode<C7RoutingKGraph>(GNodeInfo({g}, "c7_greedy"));

    gh_region = pipeline->createGGroup<SearchRegion>({g, h});
    status += pipeline->registerGElement<SearchRegion>(&gh_region, {f}, "search_region");

    status += pipeline->registerGElement<EvaRecallNode>(&i, {gh_region}, "eva_recall");

    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);
    return 0;
}
