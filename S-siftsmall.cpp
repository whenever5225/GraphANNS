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
    CStatus status = pipeline->registerGElement<ConfigAlgNPG>(&a, {}, "config_npg");
    status += pipeline->registerGElement<LoadIndex>(&f, {a}, "load_index");
    //search
    g = pipeline->createGNode<C6SeedKGraph>(GNodeInfo({}, "c6_random"));
    h = pipeline->createGNode<C7RoutingKGraph>(GNodeInfo({g}, "c7_greedy"));

    gh_region = pipeline->createGGroup<SearchRegion>({g, h});
    status += pipeline->registerGElement<SearchRegion>(&gh_region, {f}, "search_region");
    status += pipeline->registerGElement<EvaRecall>(&i, {gh_region}, "eva_recall");

    pipeline->createGParam<ParamNPG>(GRAPH_INFO_PARAM_KEY);     // pipeline执行之前，先构建 ParamNPG 参数

    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);
    return 0;
}
