cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_9 LANGUAGES CXX)

include(../cmake/Common.cmake)

add_executable(pp168 pp168.cpp)
target_link_libraries(pp168 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp169 pp169.cpp)
target_link_libraries(pp169 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp173 pp173.cpp)
target_link_libraries(pp173 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp174 pp174.cpp)
target_link_libraries(pp174 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp176 pp176.cpp)
target_link_libraries(pp176 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
