#pragma once

#include <QTimer>

class GameSpeedManager
{
public:
    GameSpeedManager();

    const QTimer& getGameTickTimer()
    { return gameTickTimer_; }

    void start();
    void stop();
    void incrementSpeed();
    void decrementSpeed();
    [[nodiscard]] int getSpeedLevel() const;
    void setSpeedLevel(int speedLevel);

private:
    QTimer gameTickTimer_;
    int speedLevel_;

    const QMap<int, int> speedLevelToDelayMsMap_{{1,  250},
                                                 {2,  230},
                                                 {3,  210},
                                                 {4,  190},
                                                 {5,  170},
                                                 {6,  150},
                                                 {7,  130},
                                                 {8,  110},
                                                 {9,  90},
                                                 {10, 70}};
};
