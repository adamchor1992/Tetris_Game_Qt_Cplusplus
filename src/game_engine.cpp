#include "game_engine.h"
#include "log_manager.h"

GameEngine::GameEngine()
{
    gameState_ = GameState::GameStopped;
    QObject::connect(&gameSpeedManager_.getGameTickTimer(), &QTimer::timeout, this, &GameEngine::gameTickHandler);
}

void GameEngine::startGame()
{
    logFile << "====================";
    logFile << "\n\nSTART GAME\n\n";

    placedSquares_ = std::make_unique<PlacedSquares>();

    gameSpeedManager_.setGameSpeed();
    scoreManager_ =std::make_unique<ScoreManager>();
    infoDisplayManager_.hideInfo();

    activeBlock_ = BlockBase::makeBlock();

    gameSpeedManager_.start();
    gameState_ = GameState::GameRunning;
}

void GameEngine::endGame()
{
    logFile << "\n\nEND GAME\n\n";
    logFile << "====================";

    gameState_ = GameState::GameStopped;
    gameSpeedManager_.stop();
    infoDisplayManager_.showRestartInfo();
}

void GameEngine::togglePause()
{
    if(gameState_ == GameState::GameRunning)
    {
        gameSpeedManager_.stop();
        gameState_ = GameState::GamePaused;
    }
    else if(gameState_ == GameState::GamePaused)
    {
        gameSpeedManager_.start();
        gameState_ = GameState::GameRunning;
    }
}

void GameEngine::gameTickHandler()
{
    if(gameState_ == GameState::GameRunning)
    {
        if(activeBlock_->isSquareOrBottomWallUnderBlock(*placedSquares_))
        {
            activeBlock_->placeBlock(*placedSquares_);

            if(QVector<int> fullRows = placedSquares_->findFullRows(); !fullRows.empty())
            {
                scoreManager_->rewardPlayerForFullRows(fullRows.size());

                for(auto rowNumber : fullRows)
                {
                    placedSquares_->removeFullRow(rowNumber);
                    placedSquares_->dropRowsAbove(rowNumber);
                }
            }

            activeBlock_ = BlockBase::makeBlock();

            if(activeBlock_->checkForOverlappingSquares(activeBlock_->getBlockCoordinates(), *placedSquares_))
            {
                endGame();
            }
        }
        else
        {
            activeBlock_->dropBlockOneLevel();
        }
    }
}

void GameEngine::processKey(const Key key)
{
    if(gameState_ == GameState::GameRunning)
    {
        if(key == Key::left)
        {
            activeBlock_->processMove(Direction::left, *placedSquares_);
        }
        else if(key == Key::right)
        {
            activeBlock_->processMove(Direction::right, *placedSquares_);
        }
        else if(key == Key::up)
        {
            activeBlock_->rotate(*placedSquares_);
        }
        else if(key == Key::down)
        {
            activeBlock_->dropAndPlaceBlock(*placedSquares_);
        }
        else if(key == Key::plus)
        {
            gameSpeedManager_.incrementSpeed();
        }
        else if(key == Key::minus)
        {
            gameSpeedManager_.decrementSpeed();
        }
        else if(key == Key::pause)
        {
            togglePause();
        }
    }
    else if(gameState_ == GameState::GameStopped)
    {
        if(key == Key::space)
        {
            startGame();
        }
    }
    else if(gameState_ == GameState::GamePaused)
    {
        if(key == Key::pause)
        {
            togglePause();
        }
    }
}
