cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_12 LANGUAGES CXX)

include(../cmake/Common.cmake)

add_executable(pp199 pp199.cpp)
target_link_libraries(pp199 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp202 pp202.cpp)
target_link_libraries(pp202 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp204 pp204.cpp)
target_link_libraries(pp204 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp206 pp206.cpp)
target_link_libraries(pp206 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp214 pp214.cpp)
target_link_libraries(pp214 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
