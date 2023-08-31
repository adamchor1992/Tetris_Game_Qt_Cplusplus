set(TEST_SOURCES
        src/main.cpp
        src/placed_squares_test.cpp
        src/block_creation_test.cpp
        src/block_movement_test.cpp
        src/block_rotation_test.cpp
        src/block_drop_test.cpp
        src/placed_squares_test.cpp)

add_subdirectory(googletest)

add_executable(${PROJECT_NAME}Test_run ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}Test_run PRIVATE src)
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest lib${PROJECT_NAME}Backend)
