cmake_minimum_required(VERSION 3.12)
project(DieHardStack)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcrypto")

add_executable(DieHardStack main.cpp DieHardStack.h)