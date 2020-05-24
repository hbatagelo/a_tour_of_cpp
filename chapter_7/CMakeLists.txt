cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_7 LANGUAGES CXX)

include(../cmake/Common.cmake)

add_executable(pp128 pp128.cpp)
target_link_libraries(pp128 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp132 pp132.cpp)
target_link_libraries(pp132 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp134 pp134.cpp)
target_link_libraries(pp134 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp136 pp136.cpp)
target_link_libraries(pp136 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
