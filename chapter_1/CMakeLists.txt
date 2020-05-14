cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_1 LANGUAGES CXX)

include(../cmake/Common.cmake)

# pp16
add_executable(pp16 pp16.cpp)
target_link_libraries(pp16 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

# pp27
add_executable(pp27 pp27.cpp)
target_link_libraries(pp27 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

# pp28
add_executable(pp28 pp28.cpp)
target_link_libraries(pp28 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
