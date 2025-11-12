cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)
project(SUPACPP_Labs)

find_package(ROOT REQUIRED)
include_directories(${ROOT_INCLUDE_DIRS})
link_directories(${ROOT_LIBRARIES})

add_executable(             HelloWorld HelloWorld.cxx)
