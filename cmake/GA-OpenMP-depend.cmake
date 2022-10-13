
find_package(OpenMP)

if (OPENMP_FOUND)
    message("[GraphANNS] OpenMP support ...")
    add_definitions(-DGA_USE_OPENMP)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -lomp")
else()
    message("[GraphANNS] OpenMP no support, recommend install for speed up.")
endif ()