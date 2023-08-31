#include "model.h"

Model::Model()
{
    gameStateManager_ = std::make_unique<GameStateManager>(gameSpeedManager_);
    reset();
}

void Model::reset()
{
    placedSquares_ = std::make_unique<PlacedSquares>();
    scoreManager_.resetScore();
}
