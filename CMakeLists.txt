cmake_minimum_required(VERSION 3.10)

project(Tetris LANGUAGES CXX)

set(QT_VERSION_MAJOR 6)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

set(INCLUDES_DIR ${PROJECT_ROOT}/inc)
set(SOURCES_DIR ${PROJECT_ROOT}/src)
set(UI_FORMS_DIR ${PROJECT_ROOT}/ui_forms)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_FORMS_DIR})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES
        ${INCLUDES_DIR}/common.h
        ${INCLUDES_DIR}/view/window.h ${SOURCES_DIR}/view/window.cpp ${UI_FORMS_DIR}/window.ui
        ${INCLUDES_DIR}/view/game_arena.h ${SOURCES_DIR}/view/game_arena.cpp
        ${INCLUDES_DIR}/model.h ${SOURCES_DIR}/model.cpp
        ${INCLUDES_DIR}/controller.h ${SOURCES_DIR}/controller.cpp
        ${INCLUDES_DIR}/tetris.h ${SOURCES_DIR}/tetris.cpp
        ${INCLUDES_DIR}/square.h ${SOURCES_DIR}/square.cpp
        ${INCLUDES_DIR}/block_factory.h ${SOURCES_DIR}/block_factory.cpp
        ${INCLUDES_DIR}/abstract_block.h ${SOURCES_DIR}/abstract_block.cpp
        ${INCLUDES_DIR}/blocks/i_block.h ${SOURCES_DIR}/blocks/i_block.cpp
        ${INCLUDES_DIR}/blocks/j_block.h ${SOURCES_DIR}/blocks/j_block.cpp
        ${INCLUDES_DIR}/blocks/l_block.h ${SOURCES_DIR}/blocks/l_block.cpp
        ${INCLUDES_DIR}/blocks/o_block.h ${SOURCES_DIR}/blocks/o_block.cpp
        ${INCLUDES_DIR}/blocks/s_block.h ${SOURCES_DIR}/blocks/s_block.cpp
        ${INCLUDES_DIR}/blocks/t_block.h ${SOURCES_DIR}/blocks/t_block.cpp
        ${INCLUDES_DIR}/blocks/z_block.h ${SOURCES_DIR}/blocks/z_block.cpp
        ${INCLUDES_DIR}/block_movement_manager.h ${SOURCES_DIR}/block_movement_manager.cpp
        ${INCLUDES_DIR}/score_manager.h ${SOURCES_DIR}/score_manager.cpp
        ${INCLUDES_DIR}/random_generator.h
        ${INCLUDES_DIR}/game_speed_manager.h ${SOURCES_DIR}/game_speed_manager.cpp
        ${INCLUDES_DIR}/placed_squares.h ${SOURCES_DIR}/placed_squares.cpp
        ${INCLUDES_DIR}/coordinates.h ${SOURCES_DIR}/coordinates.cpp
        ${INCLUDES_DIR}/coefficients.h ${SOURCES_DIR}/coefficients.cpp
        ${INCLUDES_DIR}/view/gui_config.h
        ${INCLUDES_DIR}/log_manager.h)

add_library(libTetris ${SOURCE_FILES})
target_include_directories(libTetris PUBLIC ${INCLUDES_DIR} ${INCLUDES_DIR}/blocks)
target_link_libraries(libTetris Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(Tetris WIN32 ${SOURCES_DIR}/main.cpp ${SOURCE_FILES})
target_link_libraries(Tetris PRIVATE libTetris)

if (WIN32)
    set_target_properties(Tetris PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_windows)
elseif (UNIX)
    set_target_properties(Tetris PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_linux)
endif ()

add_subdirectory(tests)
