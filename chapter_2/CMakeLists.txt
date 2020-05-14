cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_2 LANGUAGES CXX)

include(../cmake/Common.cmake)

# pp44
add_executable(pp44 pp44.cpp)
target_link_libraries(pp44 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

# pp45
add_executable(pp45 pp45.cpp)
target_link_libraries(pp45 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
