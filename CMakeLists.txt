cmake_minimum_required(VERSION 3.13)
project(nasp_sat)

set(CMAKE_CXX_STANDARD 14)

add_executable(nasp_sat main.cpp Clause.h Variable.h Formula.h Util.h)