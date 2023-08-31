#pragma once

#include "score_manager.h"
#include "game_state_manager.h"
#include "active_block_manager.h"

class Model
{
public:
    Model();
    void reset();

    [[nodiscard]] const ScoreManager& getScoreManager() const
    { return scoreManager_; }

    [[nodiscard]] ScoreManager& getScoreManager()
    { return scoreManager_; }

    GameSpeedManager& getGameSpeedManager()
    { return gameSpeedManager_; }

    [[nodiscard]] const ActiveBlockManager& getActiveBlockManager() const
    { return activeBlockManager_; }

    [[nodiscard]] ActiveBlockManager& getActiveBlockManager()
    { return activeBlockManager_; }

    [[nodiscard]] const PlacedSquares& getPlacedSquares() const
    { return *placedSquares_; }

    [[nodiscard]] PlacedSquares& getPlacedSquares()
    { return *placedSquares_; }

    [[nodiscard]] const GameStateManager& getGameStateManager() const
    { return *gameStateManager_; }

    GameStateManager& getGameStateManager()
    { return *gameStateManager_; }

private:
    std::unique_ptr<PlacedSquares> placedSquares_;
    std::unique_ptr<GameStateManager> gameStateManager_;
    ScoreManager scoreManager_;
    GameSpeedManager gameSpeedManager_;
    ActiveBlockManager activeBlockManager_;
};
