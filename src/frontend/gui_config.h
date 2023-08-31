#pragma once

#include <QColor>

namespace GuiConfig
{
    namespace GameArenaParameters
    {
        namespace Edge
        {
            const Qt::GlobalColor COLOR = Qt::white;
            const int THICKNESS = 5;
        }

        namespace LeftEdge
        {
            const int X = 0;
            const int OFFSET_X = +2;
        }

        namespace RightEdge
        {
            const int X = 305;
            const int OFFSET_X = +2;
        }

        namespace BottomEdge
        {
            const int Y = 610;
            const int OFFSET_Y = -3;
        }

        namespace TopEdge
        {
            const int Y = 0;
            const int OFFSET_Y = +2;
        }
    }

    namespace Square
    {
        const int SIZE = 30;
        const int OFFSET = +5;
        const int ROUNDED_RECT_RATIO_PERCENTAGE = 50;
    }
}
