cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(object_sample1)

add_library(module_unit
SHARED
modulea.h
modulea.cc
moduleb.h
moduleb.cc
)

add_executable(main main.cc)

target_link_libraries(main module_unit)
