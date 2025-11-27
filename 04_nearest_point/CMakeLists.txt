cmake_minimum_required(VERSION 3.20)

project(min_dist LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(target_name min_dist)

set(Sources
  src/main.cpp
)

add_executable(${target_name} ${Sources})
target_include_directories(${target_name} PRIVATE include)