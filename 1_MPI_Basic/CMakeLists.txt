cmake_minimum_required(VERSION 3.2)

project(1_MPI_Basic LANGUAGES CXX C VERSION 1.0.0)

set(SOURCES "" CACHE STRING "The sources list")

find_package(MPI REQUIRED)

add_executable(program ${SOURCES})
target_link_libraries(program MPI::MPI_CXX)
