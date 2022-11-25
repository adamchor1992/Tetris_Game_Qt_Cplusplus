#pragma once

#include "block_factory.h"
#include "abstract_block.h"
#include "placed_squares.h"
#include "random_generator.h"
#include "score_manager.h"
#include "game_speed_manager.h"

class Model
{
public:
    Model();

    [[nodiscard]] ScoreManager& getScoreManager()
    { return scoreManager_; }

    GameSpeedManager* getGameSpeedManager()
    { return &gameSpeedManager_; }

    [[nodiscard]] GameState getGameState() const
    { return gameState_; }

    [[nodiscard]] const std::unique_ptr<AbstractBlock>& getActiveBlock() const
    { return activeBlock_; }

    [[nodiscard]] const std::unique_ptr<PlacedSquares>& getPlacedSquares() const
    { return placedSquares_; }

    void resetPlacedSquares();
    AbstractBlock* generateNewBlock();
    void setGameState(GameState gameState);
    void resetScore();

private:
    std::unique_ptr<PlacedSquares> placedSquares_;
    std::unique_ptr<AbstractBlock> activeBlock_;
    ScoreManager scoreManager_;
    GameState gameState_;
    GameSpeedManager gameSpeedManager_;
    BlockFactory blockFactory_;
};
