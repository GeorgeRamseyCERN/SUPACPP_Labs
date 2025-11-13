cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)
project(SUPACPP_Labs)

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})
link_directories(${ROOT_LIBRARIES})

add_executable(             HelloWorld HelloWorld.cxx)

add_executable(             AnalyseData AnalyseData.cxx)
target_link_libraries(AnalyseData ${ROOT_LIBRARIES})
target_include_directories(AnalyseData PUBLIC "${PROJECT_SOURCE_DIR}")
