#pragma once

#include "game_speed_manager.h"

class GameStateManager
{
    enum class State
    {
        BEFORE_FIRST_RUN, RUNNING, PAUSED, STOPPED
    } state_;

public:
    explicit GameStateManager(GameSpeedManager& gameSpeedManager);
    void startGame();
    void endGame();
    void togglePause();
    [[nodiscard]] QString getCurrentStateInfoText() const;
    bool isReadyToStart() const;
    bool isRunning() const;

private:
    GameSpeedManager& gameSpeedManager_;

    std::map<State, QString> gameStateToDisplayInfoMapping_;
};
