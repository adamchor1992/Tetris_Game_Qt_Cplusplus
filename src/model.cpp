#include "model.h"

Model::Model()
{
    gameState_ = GameState::BeforeFirstRun;
    placedSquares_ = std::make_unique<PlacedSquares>();
}

AbstractBlock* Model::generateNewBlock()
{
    activeBlock_ = blockFactory_.makeRandomBlock();
    return activeBlock_.get();
}

void Model::setGameState(GameState gameState)
{
    gameState_ = gameState;
}

void Model::resetPlacedSquares()
{
    placedSquares_->removeAllPlacedSquares();
}

void Model::resetScore()
{
    scoreManager_.resetScore();
}
