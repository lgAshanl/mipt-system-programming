cmake_minimum_required(VERSION 3.12)
project(DrivelGenerator)

set(CMAKE_CXX_STANDARD 14)

add_executable(DrivelGenerator main.cpp SharedText.cpp SharedText.h)