cmake_minimum_required(VERSION 3.13)

set(OPTIONS_TARGET options)
set(WARNINGS_TARGET warnings)

add_library(${OPTIONS_TARGET} INTERFACE)
add_library(${WARNINGS_TARGET} INTERFACE)

project(chapter_15 LANGUAGES CXX)

include(../cmake/Common.cmake)

# Use pthreads
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(pp261 pp261.cpp)
target_link_libraries(pp261 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
target_link_libraries(pp261 PRIVATE Threads::Threads)

add_executable(pp264 pp264.cpp)
target_link_libraries(pp264 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
target_link_libraries(pp264 PRIVATE Threads::Threads)

add_executable(pp268 pp268.cpp)
target_link_libraries(pp268 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
target_link_libraries(pp268 PRIVATE Threads::Threads)

add_executable(pp269 pp269.cpp)
target_link_libraries(pp269 PRIVATE ${OPTIONS_TARGET} ${WARNINGS_TARGET})
target_link_libraries(pp269 PRIVATE Threads::Threads)
