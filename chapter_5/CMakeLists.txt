cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_5 LANGUAGES CXX)

include(../cmake/Common.cmake)

add_executable(main main.cpp vector.cpp vector.hpp)
target_link_libraries(main PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
