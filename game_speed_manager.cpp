#include "game_speed_manager.h"

QSlider* GameSpeedManager::m_SpeedSlider = nullptr;

GameSpeedManager::GameSpeedManager()
{
    connect(m_SpeedSlider, &QSlider::valueChanged, this, &GameSpeedManager::SetGameSpeed);
}

void GameSpeedManager::ConnectSpeedSlider(QSlider* speedSlider)
{
    m_SpeedSlider = speedSlider;
}

void GameSpeedManager::Start()
{
    m_GameTickTimer.start();
}

void GameSpeedManager::Stop()
{
    m_GameTickTimer.stop();
}

void GameSpeedManager::SetGameSpeed()
{
    const int TIME_OFFSET = 50;
    const int speedLevel = m_SpeedSlider->value();
    m_GameTickTimer.setInterval(TIME_OFFSET + speedLevel * 20);
}

void GameSpeedManager::IncrementSpeed()
{
    m_SpeedSlider->setValue(m_SpeedSlider->value() + 1);
}

void GameSpeedManager::DecrementSpeed()
{
    m_SpeedSlider->setValue(m_SpeedSlider->value() - 1);
}
