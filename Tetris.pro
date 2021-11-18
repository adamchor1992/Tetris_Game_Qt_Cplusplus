#-------------------------------------------------
#
# Project created by QtCreator 2018-08-21T21:19:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../../Tetris_Game_Qt_Cplusplus/executable_windows/Tetris
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp \
        src/game_window.cpp \
        src/game_engine.cpp \
        src/game_speed_manager.cpp \
        src/info_display_manager.cpp \
        src/score_manager.cpp \
        src/drawer.cpp \
        src/placed_squares.cpp \
        src/random_number_generator.cpp \
        src/coordinates.cpp \
        src/log_manager.cpp \
        src/block_base.cpp \
        src/blocks/i_block.cpp \
        src/blocks/j_block.cpp \
        src/blocks/l_block.cpp \
        src/blocks/o_block.cpp \
        src/blocks/s_block.cpp \
        src/blocks/t_block.cpp \
        src/blocks/z_block.cpp

HEADERS += \
        inc/common.h \
        inc/game_window.h \
        inc/game_engine.h \
        inc/game_speed_manager.h \
        inc/info_display_manager.h \
        inc/score_manager.h \
        inc/drawer.h \
        inc/placed_squares.h \
        inc/random_number_generator.h \
        inc/coordinates.h \
        inc/log_manager.h \
        inc/block_base.h \
        inc/blocks/i_block.h \
        inc/blocks/j_block.h \
        inc/blocks/l_block.h \
        inc/blocks/o_block.h \
        inc/blocks/s_block.h \
        inc/blocks/t_block.h \
        inc/blocks/z_block.h

FORMS += \
        ui_forms/game_window.ui
