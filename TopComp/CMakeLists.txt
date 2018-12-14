cmake_minimum_required(VERSION 3.12)
project(TopComp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto")

add_executable(TopComp main.cpp Computer.h Computer.cpp DieHardStack.h)