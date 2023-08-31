#pragma once

#include "speed_level.h"
#include <QTimer>

class GameSpeedManager
{
public:
    GameSpeedManager();

    const QTimer& getGameTickTimer()
    { return gameTickTimer_; }

    void startTimer();
    void stopTimer();

    void incrementSpeed();
    void decrementSpeed();

    [[nodiscard]] int getSpeedLevelInteger() const;

    void setSpeedLevel(int speedLevel);

private:
    void updateInterval();

    QTimer gameTickTimer_;
    SpeedLevel speedLevel_;
};
