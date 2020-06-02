cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_13 LANGUAGES CXX)

include(../cmake/Common.cmake)

add_executable(pp228 pp228.cpp)
target_link_libraries(pp228 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp230 pp230.cpp)
target_link_libraries(pp230 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp234 pp234.cpp)
target_link_libraries(pp234 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp235 pp235.cpp)
target_link_libraries(pp235 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp241 pp241.cpp)
target_link_libraries(pp241 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp243 pp243.cpp)
target_link_libraries(pp243 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
