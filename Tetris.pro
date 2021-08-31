#-------------------------------------------------
#
# Project created by QtCreator 2018-08-21T21:19:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris
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
        main.cpp \
        game_window.cpp \
        game_engine.cpp \
        game_speed_manager.cpp \
        info_display_manager.cpp \
        score_manager.cpp \
        drawer.cpp \
        placed_squares.cpp \
        random_number_generator.cpp \
        coordinates.cpp \
        block_base.cpp \
        blocks/i_block.cpp \
        blocks/j_block.cpp \
        blocks/l_block.cpp \
        blocks/o_block.cpp \
        blocks/s_block.cpp \
        blocks/t_block.cpp \
        blocks/z_block.cpp

HEADERS += \
        game_window.h \
        game_engine.h \
        game_speed_manager.h \
        info_display_manager.h \
        score_manager.h \
        drawer.h \
        placed_squares.h \
        random_number_generator.h \
        utilities.h \
        coordinates.cpp \
        block_base.h \
        blocks/i_block.h \
        blocks/j_block.h \
        blocks/l_block.h \
        blocks/o_block.h \
        blocks/s_block.h \
        blocks/t_block.h \
        blocks/z_block.h

FORMS += \
        game_window.ui
