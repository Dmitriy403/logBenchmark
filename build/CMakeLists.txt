cmake_minimum_required(VERSION 2.8)
project(logBenchmark)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D _DEBUG")

find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})

find_package(POCO REQUIRED)
include_directories(${POCO_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include) 

add_executable(logbench ../src/Benchmark.cpp ../src/PocoBenchmark.cpp ../src/GlogBenchmark.cpp ../src/logbench.cpp)
target_link_libraries(logbench ${GLOG_LIBRARIES} ${POCO_LIBRARIES})

