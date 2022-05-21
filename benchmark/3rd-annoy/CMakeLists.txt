cmake_minimum_required(VERSION 3.2.5)
project(3rd-annoy-pipeline)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE CGRAPH_SRC_LIST "../../CGraph/src/*.cpp")
include(../../CGraph/cmake/CGraph-env-include.cmake)

add_executable(3rd-annoy-pipeline
        annoy_pipeline.cpp
        ${CGRAPH_SRC_LIST}
        )
