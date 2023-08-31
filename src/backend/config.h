#pragma once

#include "speed_level.h"
#include "coordinates.h"
#include <QColor>
#include <chrono>
#include <map>

namespace Config
{
    namespace Arena
    {
        const int MINIMUM_X = 1;
        const int MINIMUM_Y = 1;
        const int MAXIMUM_X = 10;
        const int MAXIMUM_Y = 20;
        constexpr int BOTTOM_EDGE_Y = MAXIMUM_Y + 1;
    }

    namespace Block
    {
        const std::vector<QColor> BLOCK_COLORS = {Qt::cyan, Qt::blue, QColor(255, 165, 0), Qt::yellow, Qt::green, Qt::magenta, Qt::red};
        static constexpr Coordinates STARTING_CENTRAL_SQUARE_COORDINATES{5, 2};
    }

    namespace Speed
    {
        const int DEFAULT_SPEED_LEVEL = 5;
        const int MIN_SPEED_LEVEL = 1;
        const int MAX_SPEED_LEVEL = 10;

        using namespace std::chrono_literals;

        const std::map<SpeedLevel, std::chrono::duration<int, std::milli>> SPEED_LEVEL_TO_TIMER_INTERVAL_MAP{{SpeedLevel(1),  250ms},
                                                                                                             {SpeedLevel(2),  230ms},
                                                                                                             {SpeedLevel(3),  210ms},
                                                                                                             {SpeedLevel(4),  190ms},
                                                                                                             {SpeedLevel(5),  170ms},
                                                                                                             {SpeedLevel(6),  150ms},
                                                                                                             {SpeedLevel(7),  130ms},
                                                                                                             {SpeedLevel(8),  110ms},
                                                                                                             {SpeedLevel(9),  90ms},
                                                                                                             {SpeedLevel(10), 70ms}};
    }
}

namespace InfoDisplayOptions
{
    const QString NO_INFO{""};
    const QString FIRST_START_INFO{"PRESS SPACE TO START"};
    const QString RESTART_INFO{"GAME OVER\nPRESS SPACE TO RESTART"};
    const QString PAUSED_INFO{"PAUSED"};
}
