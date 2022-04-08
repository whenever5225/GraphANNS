/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: main.cpp
@Time: 2022/3/26 9:19 PM
@Desc: TODO
***************************/
#include "src/data/load_for_build.h"
#include "src/components/c1_initialization/c1_nssg.h"
#include "src/components/c2_candidate/c2_2order_neighbor.h"
#include "src/components/c3_neighbor/c3_nsg.h"
#include "src/data/save_index.h"
#include "src/data/load_for_search.h"
#include "src/data/load_index.h"
#include "src/components/c6_seed/c6_random.h"
#include "src/components/c7_routing/c7_greedy.h"
#include "src/regions/search_region.h"
#include "src/data/load_for_eva.h"
#include "src/evaluation/eva_recall.h"

using namespace CGraph;

int main(){
    GPipelinePtr pipeline = GPipelineFactory::create();

    GElementPtr a, b, c, d, e, f, g, h, i, j, k, a_region= nullptr;
    // build
    CStatus status = pipeline->registerGElement<LoadForBuild>(&a, {}, "base_data");
    status += pipeline->registerGElement<C1NSSG>(&b, {a}, "c1_nssg");
    status += pipeline->registerGElement<C2TwoOrderNeighbor>(&c, {a,b}, "c2_nssg");
    status += pipeline->registerGElement<C3NSG>(&d, {a,b,c}, "c3_nsg");
    status += pipeline->registerGElement<SaveIndex>(&e, {a,b,c,d}, "save_index");

    status += pipeline->registerGElement<LoadForSearch>(&f, {}, "load_for_search");
    status += pipeline->registerGElement<LoadIndex>(&g, {f}, "load_index");

    //search
    h = pipeline->createGNode<C6Random>(GNodeInfo({}, "c6_random"));
    i = pipeline->createGNode<C7Greedy>(GNodeInfo({h}, "c7_greedy"));

    a_region = pipeline->createGGroup<SearchRegion>({h,i});

    status += pipeline->registerGElement<SearchRegion>(&a_region, {f,g}, "search_region");
    status += pipeline->registerGElement<LoadForEva>(&j, {a_region}, "load_for_eva");
    status += pipeline->registerGElement<EvaRecall>(&k, {j}, "eva_recall");

    status += pipeline->process();
    GPipelineFactory::remove(pipeline);
    return 0;
}
