cmake_minimum_required(VERSION 3.10)

project(Tetris LANGUAGES CXX)

set(QT_VERSION_MAJOR 6)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})

set(MAIN_PROJECT_INCLUDES_PATH ${PROJECT_DIR}/inc)
set(MAIN_PROJECT_SOURCES_PATH ${PROJECT_DIR}/src)
set(MAIN_PROJECT_UI_FORMS_PATH ${PROJECT_DIR}/ui_forms)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${MAIN_PROJECT_UI_FORMS_PATH})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(MAIN_PROJECT_SOURCES
    ${MAIN_PROJECT_SOURCES_PATH}/main.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/common.h
    ${MAIN_PROJECT_INCLUDES_PATH}/game_window.h ${MAIN_PROJECT_SOURCES_PATH}/game_window.cpp ${MAIN_PROJECT_UI_FORMS_PATH}/game_window.ui
    ${MAIN_PROJECT_INCLUDES_PATH}/game_engine.h ${MAIN_PROJECT_SOURCES_PATH}/game_engine.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/block_base.h ${MAIN_PROJECT_SOURCES_PATH}/block_base.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/blocks/i_block ${MAIN_PROJECT_SOURCES_PATH}/blocks/i_block.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/blocks/j_block ${MAIN_PROJECT_SOURCES_PATH}/blocks/j_block.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/blocks/l_block ${MAIN_PROJECT_SOURCES_PATH}/blocks/l_block.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/blocks/o_block ${MAIN_PROJECT_SOURCES_PATH}/blocks/o_block.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/blocks/s_block ${MAIN_PROJECT_SOURCES_PATH}/blocks/s_block.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/blocks/t_block ${MAIN_PROJECT_SOURCES_PATH}/blocks/t_block.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/blocks/z_block ${MAIN_PROJECT_SOURCES_PATH}/blocks/z_block.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/drawer.h ${MAIN_PROJECT_SOURCES_PATH}/drawer.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/score_manager.h ${MAIN_PROJECT_SOURCES_PATH}/score_manager.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/random_number_generator.h ${MAIN_PROJECT_SOURCES_PATH}/random_number_generator.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/info_display_manager.h ${MAIN_PROJECT_SOURCES_PATH}/info_display_manager.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/game_speed_manager.h ${MAIN_PROJECT_SOURCES_PATH}/game_speed_manager.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/placed_squares.h ${MAIN_PROJECT_SOURCES_PATH}/placed_squares.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/coordinates.h ${MAIN_PROJECT_SOURCES_PATH}/coordinates.cpp
    ${MAIN_PROJECT_INCLUDES_PATH}/log_manager.h ${MAIN_PROJECT_SOURCES_PATH}/log_manager.cpp
)

add_executable(${PROJECT_NAME} WIN32 ${MAIN_PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${MAIN_PROJECT_INCLUDES_PATH} ${MAIN_PROJECT_INCLUDES_PATH}/blocks)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/executable_windows)
