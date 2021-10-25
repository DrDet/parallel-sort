cmake_minimum_required(VERSION 3.16)
project(parsort)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Werror -O3)

add_executable(parsort main.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(parsort PUBLIC OpenMP::OpenMP_CXX)
endif()

