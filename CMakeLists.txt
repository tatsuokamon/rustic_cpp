cmake_minimum_required(VERSION 3.20)
project(rustic_project)

add_library(rustic src/rustic.cpp)
target_include_directories(rustic PUBLIC include)
