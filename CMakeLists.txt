cmake_minimum_required(VERSION 3.24)

project(MortisUtils LANGUAGES CXX)

include(cmake/config.cmake)
include(cmake/package.cmake)
include(cmake/function.cmake)

add_subdirectory(src)
#add_subdirectory(test) 