/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: hnsw_pipeline.cpp
@Time: 2022/6/4 00:51
@Desc: 
***************************/

#include "hnsw_include.h"

using namespace CGraph;

void hnsw_pipeline() {
    GElementPtr prepare, algo, show = nullptr;
    auto pipeline = GPipelineFactory::create();

    /**
     * change this param to control the procedure for train or search.
     * please run train mode before search.
     * param in [ANN_TRAIN, ANN_SEARCH]
     */
    HNSW_FUNC_TYPE = DAnnFuncType::ANN_TRAIN;

    CStatus status = pipeline->registerGElement<HnswPrepareNode>(&prepare, {}, "prepare");
    status += pipeline->registerGElement<HnswAlgoNode>(&algo, {prepare}, "algo");
    status += pipeline->registerGElement<HnswShowNode>(&show, {algo}, "show");

    /**
     * add trace aspect for all element in this pipeline
     */
    pipeline->addGAspect<TraceAspect>();

    status += pipeline->process();
    if (!status.isOK()) {
        printf("error code is [%d], info is [%s]", status.getCode(), status.getInfo().c_str());
    }

    GPipelineFactory::clear();
}

int main() {
    hnsw_pipeline();
}
