cmake_minimum_required(VERSION 3.2.5)
project(GraphANNS)

set(CMAKE_CXX_STANDARD 17)

include_directories(CGraph)

file(GLOB_RECURSE CGRAPH_SRC_LIST "CGraph/src/*.cpp")

include(CGraph/cmake/CGraph-env-include.cmake)

set(TUTORIAL_LIST
        T-siftsmall
        S-siftsmall
        )

foreach(tut ${TUTORIAL_LIST})
    add_executable(${tut} ${tut}.cpp ${CGRAPH_SRC_LIST})
endforeach()
