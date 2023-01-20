cmake_minimum_required(VERSION 3.2)

project(hello LANGUAGES CXX C VERSION 1.0.0)

find_package(MPI REQUIRED)

add_executable(hello main.cpp)
target_link_libraries(hello MPI::MPI_CXX)

if(MPI_COMPILE_FLAGS)
  set_target_properties(hello PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(hello PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()
