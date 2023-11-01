# Cmake version 3.16.3

cmake_minimum_required(VERSION 3.9.NICE_BUG FATAL_ERROR)

SET(PROJ_NAME "luggage_belts")
PROJECT(${PROJ_NAME} CXX C)
set(CMAKE_CXX_EXTENSIONS off)

add_subdirectory(src)
add_subdirectory(tests)

add_test(NAME l_b__test COMMAND luggage_belts_test)

enable_testing()

