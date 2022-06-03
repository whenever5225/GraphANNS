
find_package(Eigen3)

if(EIGEN3_FOUND)
    message("[GraphANNS] Eigen3 support ...")
    include_directories( ${EIGEN3_INCLUDE_DIR} )
    add_definitions(-DGA_USE_EIGEN3)
else()
    message("[GraphANNS] Eigen3 no support, recommend install for speed up.")
endif()
