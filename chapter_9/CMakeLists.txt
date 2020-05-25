cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_9 LANGUAGES CXX)

include(../cmake/Common.cmake)

add_executable(pp148 pp148.cpp)
target_link_libraries(pp148 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp153 pp153.cpp)
target_link_libraries(pp153 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
