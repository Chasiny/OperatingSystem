cmake_minimum_required(VERSION 3.8)
project(Experiment01)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main01.cpp msg/msgsend.cpp msg/msgrec.cpp)
add_executable(Experiment01 ${SOURCE_FILES})