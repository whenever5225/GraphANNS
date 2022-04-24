cmake_minimum_required(VERSION 3.2.5)
project(GraphANNS)

set(CMAKE_CXX_STANDARD 17)

include_directories(CGraph)

file(GLOB_RECURSE SRC_LIST "CGraph/src/*.cpp")


IF(APPLE)
    # It does not support automatic generation of session information for non-Mac platform
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -finline-functions -Wno-deprecated-declarations")
    add_definitions(-D_GENERATE_SESSION_)
    add_definitions(-D_ENABLE_LIKELY_)
ELSEIF(UNIX)
    # Adding multi-threads to linux platform
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -Wno-format-overflow")
    add_definitions(-D_ENABLE_LIKELY_)
ENDIF()

add_executable(GraphANNS ${SRC_LIST} main.cpp)