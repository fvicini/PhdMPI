cmake_minimum_required(VERSION 3.2)

project(hello LANGUAGES CXX C VERSION 1.0.0)

find_package(MPI REQUIRED)

add_executable(hello main.cpp)
target_link_libraries(hello MPI::MPI_CXX)
