cmake_minimum_required(VERSION 3.20)
project(LongMath)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)

include_directories(LongNumber)
add_subdirectory(LongNumber)


add_library(Pi STATIC pi.cpp pi.h)

target_link_libraries(main LongNumber)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests MathTest.cpp)
target_link_libraries(tests LongNumber)
