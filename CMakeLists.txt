cmake_minimum_required(VERSION 2.4)
project(FDCL-VICON)

set (CMAKE_CXX_STANDARD 11)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories("/usr/local/include/")
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/libraries/eigen)

link_directories("/usr/local/lib/")

## Main #######################################################################

set(fdcl_vicon_src
    src/fdcl_vicon.cpp
    src/fdcl_matrix_utils.cpp
   )
add_library(fdcl_vicon STATIC ${fdcl_vicon_src})


add_executable(test_fdcl_vicon 
    src/main.cpp
)
target_compile_options(test_fdcl_vicon
    PRIVATE -lvrpn -lquat -lrt -pthread -O3 -std=c++11
    )
target_link_libraries(test_fdcl_vicon
    fdcl_vicon
    Threads::Threads
    vrpn
    )
