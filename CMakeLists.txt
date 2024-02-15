cmake_minimum_required(VERSION 3.26)
project(LongMath)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)

include_directories(LongNumber)

add_subdirectory(LongNumber)

target_link_libraries(main LongNumber)
