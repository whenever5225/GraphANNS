/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: main.cpp
@Time: 2022/4/12 10:23 AM
@Desc:
***************************/

#include "../src/graph_anns.h"

using namespace CGraph;

int main() {
    GPipelinePtr pipeline = GPipelineFactory::create();

    GElementPtr a, b, c, d, e, f, g, h, i, j, k, l, de_region, ij_region= nullptr;
    // build
    CStatus status = pipeline->registerGElement<ConfigNPG>(&a, {}, "config_npg");
    status += pipeline->registerGElement<LoadForBuild>(&b, {a}, "base_data");
    status += pipeline->registerGElement<C1InitializationKGraph>(&c, {b}, "c1_nssg");

//    d = pipeline->createGNode<C2CandidateNSSG>(GNodeInfo({}, "c2_nssg"));
//    e = pipeline->createGNode<C3NeighborNSG>(GNodeInfo({d}, "c3_nsg"));
//    de_region = pipeline->createGGroup<BuildRegion>({d, e});
//
//    status += pipeline->registerGElement<BuildRegion>(&de_region, {c}, "build_region");

    status += pipeline->registerGElement<C2CandidateNSSGV1>(&d, {c}, "c2_nssg");
    status += pipeline->registerGElement<C3NeighborNSGV1>(&e, {d}, "c3_nsg");
    status += pipeline->registerGElement<SaveIndex>(&f, {e}, "save_index");

    status += pipeline->registerGElement<LoadForSearch>(&g, {f}, "load_for_search");
    status += pipeline->registerGElement<LoadIndex>(&h, {g}, "load_index");

    //search
    i = pipeline->createGNode<C6SeedKGraph>(GNodeInfo({}, "c6_random"));
    j = pipeline->createGNode<C7RoutingKGraph>(GNodeInfo({i}, "c7_greedy"));

    ij_region = pipeline->createGGroup<SearchRegion>({i, j});

    status += pipeline->registerGElement<SearchRegion>(&ij_region, {g, h}, "search_region");
    status += pipeline->registerGElement<LoadForEva>(&k, {ij_region}, "load_for_eva");
    status += pipeline->registerGElement<EvaRecall>(&l, {k}, "eva_recall");

    status += pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("process graph error, error info is [%s]", status.getInfo().c_str());
        return 0;
    }
    GPipelineFactory::remove(pipeline);
    return 0;
}