#include <QMap>
#include "game_speed_manager.h"
#include "common.h"

GameSpeedManager::GameSpeedManager()
{
    speedLevel_ = Config::Speed::DEFAULT_SPEED_LEVEL;
}

void GameSpeedManager::start()
{
    gameTickTimer_.start();
}

void GameSpeedManager::stop()
{
    gameTickTimer_.stop();
}

void GameSpeedManager::setSpeedLevel(int speedLevel)
{
    gameTickTimer_.setInterval(speedLevelToDelayMsMap_.value(speedLevel));
}

void GameSpeedManager::incrementSpeed()
{
    if(speedLevel_ < Config::Speed::MAX_SPEED_LEVEL)
    {
        ++speedLevel_;
    }
}

void GameSpeedManager::decrementSpeed()
{
    if(speedLevel_ > Config::Speed::MIN_SPEED_LEVEL)
    {
        --speedLevel_;
    }
}

int GameSpeedManager::getSpeedLevel() const
{
    return speedLevel_;
}
