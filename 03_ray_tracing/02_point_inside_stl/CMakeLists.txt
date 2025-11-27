cmake_minimum_required(VERSION 3.10)

project(line_triangle_interection LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(target_name line_tri)

set(Sources
  src/main.cpp
  src/VTKReader.cpp
)

add_executable(${target_name} ${Sources})

target_include_directories(${target_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${target_name} PRIVATE ${VTK_LIBRARIES})
