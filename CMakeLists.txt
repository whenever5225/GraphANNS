cmake_minimum_required(VERSION 3.20)
project(GraphANNS)

set(CMAKE_CXX_STANDARD 17)

include_directories(CGraph)

file(GLOB_RECURSE SRC_LIST "CGraph/src/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -finline-functions -Wno-deprecated-declarations")

add_executable(GraphANNS ${SRC_LIST} main.cpp src/components/c1_initialization/c1_random_graph.h src/params/vector_params.h src/params/graph_params.h src/components/c1_initialization/function/gen_random_id.h src/distance/distance_naive.h src/components/c2_candidate/c2_2order_neighbor.h src/components/c1_initialization/c1_nssg.h src/params/alg/npg_params.h src/components/c3_neighbor/c3_nsg.h src/data/save_index.h src/data/load_for_search.h src/data/read_vecs.h src/data/load_for_build.h src/data/load_index.h src/params/search_params.h src/components/c6_seed/c6_random.h src/components/c7_routing/c7_greedy.h src/regions/search_region.h src/components/c7_routing/function/insert_into_pool.h src/data/load_for_eva.h src/evaluation/eva_recall.h src/params/eva_params.h)