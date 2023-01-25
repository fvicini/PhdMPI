
cmake_minimum_required(VERSION 3.2)
project(1_MPI_Basic LANGUAGES CXX C VERSION 1.0.0) # Name of the project

set(SOURCES "" CACHE STRING "The sources list") # Variable which stores the cpp files

find_package(MPI REQUIRED) # Find the MPI library

add_executable(${PROJECT_NAME} ${SOURCES}) # add list of files to executable
target_link_libraries(${PROJECT_NAME} MPI::MPI_CXX) # Link MPI library
