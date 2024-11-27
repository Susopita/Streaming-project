cmake_minimum_required(VERSION 3.29)
project(Streaming LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR})

include_directories(include)
include_directories(backend)
include_directories(frontend)