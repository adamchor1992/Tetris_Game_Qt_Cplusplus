#include "game_speed_manager.h"

GameSpeedManager::GameSpeedManager()
{
    connect(speedSlider_, &QSlider::valueChanged, this, &GameSpeedManager::setGameSpeed);
}

void GameSpeedManager::connectSpeedSlider(QSlider* speedSlider)
{
    speedSlider_ = speedSlider;
}

void GameSpeedManager::start()
{
    gameTickTimer_.start();
}

void GameSpeedManager::stop()
{
    gameTickTimer_.stop();
}

void GameSpeedManager::setGameSpeed()
{
    const int timeOffset = 50;
    const int speedLevel = speedSlider_->value();
    gameTickTimer_.setInterval(timeOffset + speedLevel * 20);
}

void GameSpeedManager::incrementSpeed()
{
    /*Subtracting means increasing speed*/
    speedSlider_->setValue(speedSlider_->value() - 1);
}

void GameSpeedManager::decrementSpeed()
{
    /*Adding means decreasing speed*/
    speedSlider_->setValue(speedSlider_->value() + 1);
}
