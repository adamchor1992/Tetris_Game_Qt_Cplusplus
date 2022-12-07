cmake_minimum_required(VERSION 3.10)

project(TetrisTest LANGUAGES CXX)

set(TEST_SOURCES
        src/main.cpp
        src/placed_squares_test.cpp
        src/block_test.cpp)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(TetrisTest_run ${TEST_SOURCES})
target_include_directories(TetrisTest_run PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(TetrisTest_run gtest gtest_main libTetris)
