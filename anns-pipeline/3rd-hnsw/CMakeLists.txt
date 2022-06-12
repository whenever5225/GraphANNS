cmake_minimum_required(VERSION 3.5.0)
project(3rd-hnsw-pipeline)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CGRAPH_SRC_LIST "../../CGraph/src/*.cpp")
include(../../CGraph/cmake/CGraph-env-include.cmake)

add_executable(3rd-hnsw-pipeline
        hnsw_pipeline.cpp
        ${CGRAPH_SRC_LIST}
        )
