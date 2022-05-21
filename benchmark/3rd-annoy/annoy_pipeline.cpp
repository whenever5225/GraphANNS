/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: annoy_pipeline.cpp
@Time: 2022/5/21 15:12
@Desc: 
***************************/

#include "annoy_algo_node.h"
#include "annoy_show_node.h"

using namespace std;
using namespace CGraph;

int main() {
    GElementPtr algo, show = nullptr;
    auto pipeline = GPipelineFactory::create();

    /**
     * change `ANNOY_FUNC_TYPE` in annoy_define.h to control the procedure for train or search.
     * please run train mode before search.
     * many other param is also given.
     */
    CStatus status = pipeline->registerGElement<AnnoyAlgoNode>(&algo, {}, "algo");
    status += pipeline->registerGElement<AnnoyShowNode>(&show, {algo}, "show");
    status += pipeline->process();

    GPipelineFactory::clear();
    return 0;
}