#pragma once

#include <QSlider>
#include <QTimer>

class GameSpeedManager : public QObject
{
    Q_OBJECT

public:
    GameSpeedManager();
    static void ConnectSpeedSlider(QSlider* speedSlider);
    const QTimer& GetGameTickTimer() {return m_GameTickTimer;}
    void Start();
    void Stop();
    void IncrementSpeed();
    void DecrementSpeed();

private:
    static QSlider* m_SpeedSlider;
    QTimer m_GameTickTimer;

public slots:
    void SetGameSpeed();
};
