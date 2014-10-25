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

# tags
set_source_files_properties(tags PROPERTIES GENERATED true)
add_custom_target(tags
    COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extra=+q --exclude=.git --exclude=*.md --exclude=*.sh ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# only make it a dependency of the project if the ctags program is available
find_program(CTAGS_PATH ctags)
if(CTAGS_PATH)
    message(STATUS "Found ctags: ${CTAGS_PATH}")
    add_dependencies(logbench tags)
endif(CTAGS_PATH)


