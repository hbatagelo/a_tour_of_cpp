cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_6 LANGUAGES CXX)

include(../cmake/Common.cmake)

add_executable(main main.cpp vector.cpp vector.hpp)
target_link_libraries(main PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp116 pp116.cpp vector.cpp vector.hpp)
target_link_libraries(pp116 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp117 pp117.cpp vector.cpp vector.hpp)
target_link_libraries(pp117 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp119 pp119.cpp shape.cpp shape.hpp)
target_link_libraries(pp119 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp121 pp121.cpp)
target_link_libraries(pp121 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})

add_executable(pp122 pp122.cpp)
target_link_libraries(pp122 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
