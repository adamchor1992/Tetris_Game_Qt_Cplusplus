#pragma once

#include <QColor>

enum class Direction
{
    left = 1, right = 2
};

enum class BlockShape
{
    S, Z, I, J, L, O, T
};

enum class Key
{
    left, right, up, down, plus, minus, pause, space
};

namespace GameParameters
{
    namespace Arena
    {
        const int minBlockRows = 1;
        const int maxBlockRows = 20;
        const int minBlockColumns = 1;
        const int maxBlockColumns = 10;
    }

    namespace Block
    {
        const QVector<QColor> blockColors = {Qt::red, Qt::blue, Qt::green, Qt::yellow, Qt::cyan, Qt::magenta};
        const QVector<BlockShape> blockShapes = {BlockShape::S, BlockShape::Z, BlockShape::I, BlockShape::J, BlockShape::L, BlockShape::O, BlockShape::T};
    }
}

enum class GameState
{
    BeforeFirstRun, Running, Paused, Stopped
};

namespace InfoDisplayOptions
{
    const QString NO_INFO{""};
    const QString FIRST_START_INFO{"PRESS SPACE TO START"};
    const QString RESTART_INFO{"GAME OVER\nPRESS SPACE TO RESTART"};
    const QString PAUSED_INFO{"PAUSED"};
}

namespace Config
{
    namespace Speed
    {
        const int DEFAULT_SPEED_LEVEL = 5;
        const int MIN_SPEED_LEVEL = 1;
        const int MAX_SPEED_LEVEL = 10;
    }
}
