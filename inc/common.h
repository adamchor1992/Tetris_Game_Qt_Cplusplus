#pragma once

#include <QColor>

namespace GameArenaParameters
{
    const int wallThickness = 5;
    const Qt::GlobalColor wallColor = Qt::white;
    const int wallOffset = 5;
    const int leftBorderX = 0;
    const int leftBorderOffsetX = +2;
    const int rightBorderX = 305;
    const int rightBorderOffsetX = +2;
    const int bottomY = 610;
    const int bottomOffsetY = -3;
    const int topY = 0;
    const int topOffsetY = +2;
    const int minBlockRows = 1;
    const int maxBlockRows = 20;
    const int minBlockColumns = 1;
    const int maxBlockColumns = 10;
    const int blockSquareSize = 30;
}

enum class Direction
{
    left = 1,
    right = 2
};

enum class BlockShape
{
    S, Z, I, J, L, O, T, RANDOM
};
