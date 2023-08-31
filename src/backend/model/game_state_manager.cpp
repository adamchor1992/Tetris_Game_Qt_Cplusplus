#include "game_state_manager.h"
#include "config.h"

GameStateManager::GameStateManager(GameSpeedManager& gameSpeedManager) : gameSpeedManager_(gameSpeedManager), state_(State::BEFORE_FIRST_RUN)
{
    gameStateToDisplayInfoMapping_.insert({State::BEFORE_FIRST_RUN, InfoDisplayOptions::FIRST_START_INFO});
    gameStateToDisplayInfoMapping_.insert({State::RUNNING, InfoDisplayOptions::NO_INFO});
    gameStateToDisplayInfoMapping_.insert({State::STOPPED, InfoDisplayOptions::RESTART_INFO});
    gameStateToDisplayInfoMapping_.insert({State::PAUSED, InfoDisplayOptions::PAUSED_INFO});
}

void GameStateManager::startGame()
{
    gameSpeedManager_.startTimer();
    state_ = State::RUNNING;
}

void GameStateManager::endGame()
{
    gameSpeedManager_.stopTimer();
    state_ = State::STOPPED;
}

void GameStateManager::togglePause()
{
    if(state_ == State::PAUSED)
    {
        state_ = State::RUNNING;
        gameSpeedManager_.startTimer();
    }
    else if(state_ == State::RUNNING)
    {
        state_ = State::PAUSED;
        gameSpeedManager_.stopTimer();
    }
}

QString GameStateManager::getCurrentStateInfoText() const
{
    return gameStateToDisplayInfoMapping_.at(state_);
}

bool GameStateManager::isReadyToStart() const
{
    return state_ == State::BEFORE_FIRST_RUN || state_ == State::STOPPED;
}

bool GameStateManager::isRunning() const
{
    return state_ == State::RUNNING;
}
