cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_2 LANGUAGES CXX)

include(../cmake/Common.cmake)

add_executable(user user.cpp vector.cpp vector.hpp)
target_link_libraries(user PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp67 pp67.cpp)
target_link_libraries(pp67 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
