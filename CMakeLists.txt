cmake_minimum_required(VERSION 2.8)
project(logBenchmark)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMPL_OPTS "-Wall -std=c++11 -pedantic -Werror")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMPL_OPTS}")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D _DEBUG ${CMPL_OPTS}")
ELSEIF(MSVC)
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_DEBUG")
ENDIF()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) 

add_executable(logbench src/Benchmark.cpp src/PocoBenchmark.cpp src/GlogBenchmark.cpp src/logbench.cpp)
target_link_libraries(logbench PocoFoundation glog)
