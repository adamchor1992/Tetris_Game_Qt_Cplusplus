#pragma once

#include <QColor>

namespace GameArenaParameters
{
    const int WALL_THICKNESS = 5;
    const Qt::GlobalColor WALL_COLOR = Qt::white;
    const int WALL_OFFSET = 5;
    const int LEFT_BORDER_X = 0;
    const int LEFT_BORDER_X_OFFSET = +2;
    const int RIGHT_BORDER_X = 305;
    const int RIGHT_BORDER_X_OFFSET = +2;
    const int BOTTOM_Y = 610;
    const int BOTTOM_Y_OFFSET = -3;
    const int TOP_Y = 0;
    const int TOP_Y_OFFSET = +2;
    const int MIN_BLOCK_ROWS = 1;
    const int MAX_BLOCK_ROWS = 20;
    const int MIN_BLOCK_COLUMNS = 1;
    const int MAX_BLOCK_COLUMNS = 10;
    const int BLOCK_SQUARE_SIZE = 30;
}

enum class Direction
{
    left = 1,
    right = 2
};
