/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: annoy_pipeline.cpp
@Time: 2022/5/21 15:12
@Desc: 
***************************/

#include "annoy_include.h"

using namespace CGraph;

int main() {
    GElementPtr prepare, algo, show = nullptr;
    auto pipeline = GPipelineFactory::create();

    /**
     * change this param to control the procedure for train or search.
     * please run train mode before search.
     * param in [ANN_TRAIN, ANN_SEARCH]
     */
    ANNOY_FUNC_TYPE = DAnnFuncType::ANN_TRAIN;

    /**
     * build annoy pipeline
     * many other param is also given in `annoy_define.h`
     */
    CStatus status = pipeline->registerGElement<AnnoyPrepareNode>(&prepare, {}, "prepare");
    status += pipeline->registerGElement<AnnoyAlgoNode>(&algo, {prepare}, "algo");
    status += pipeline->registerGElement<AnnoyShowNode>(&show, {algo}, "show");

    /**
     * run this annoy pipeline
     */
    status += pipeline->process();
    if (!status.isOK()) {
        printf("error code is [%d], info is [%s]", status.getCode(), status.getInfo().c_str());
    }

    GPipelineFactory::clear();
    return 0;
}