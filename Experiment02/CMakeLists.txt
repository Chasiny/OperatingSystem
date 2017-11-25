cmake_minimum_required(VERSION 3.8)
project(Experiment02)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Banker.cpp Banker.h Global.h Process.cpp Process.h)
add_executable(Experiment02 ${SOURCE_FILES})