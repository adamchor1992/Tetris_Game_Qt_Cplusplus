#pragma once

#include <QSlider>
#include <QTimer>

class GameSpeedManager : public QObject
{
    Q_OBJECT

public:
    GameSpeedManager();
    static void connectSpeedSlider(QSlider* speedSlider);
    const QTimer& getGameTickTimer() {return gameTickTimer_;}
    void start();
    void stop();
    void incrementSpeed();
    void decrementSpeed();

public slots:
    void setGameSpeed();

private:
    inline static QSlider* speedSlider_ = nullptr;
    QTimer gameTickTimer_;
};
