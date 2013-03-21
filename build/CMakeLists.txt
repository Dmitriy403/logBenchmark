cmake_minimum_required(VERSION 2.8)
project(logBenchmark)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x ")

IF(POCO_PATH AND POCO_LIB_PATH)
MESSAGE(STATUS "use custom POCO_PATHS: ${POCO_PATH} |<>| ${POCO_LIB_PATH}")
include_directories("${POCO_PATH}/Foundation/include")
add_library(poco_opt UNKNOWN IMPORTED)
set_target_properties(poco_opt PROPERTIES IMPORTED_LOCATION "${POCO_LIB_PATH}/libPocoFoundation.so")
add_library(poco_dbg UNKNOWN IMPORTED)
set_target_properties(poco_dbg PROPERTIES IMPORTED_LOCATION "${POCO_LIB_PATH}/libPocoFoundationd.so")
ENDIF(POCO_PATH AND POCO_LIB_PATH)

find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include) 

add_executable(logbench ../src/Benchmark.cpp ../src/PocoBenchmark.cpp ../src/GlogBenchmark.cpp ../src/logbench.cpp)
target_link_libraries(logbench ${GLOG_LIBRARIES} optimized poco_opt debug poco_dbg)

