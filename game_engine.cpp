#include "game_engine.h"
#include "log_manager.h"

GameEngine::GameEngine()
{
    gameState_ = GameState::GameStopped;
    QObject::connect(&gameSpeedManager_.getGameTickTimer(), &QTimer::timeout, this, &GameEngine::gameTickHandler);
}

void GameEngine::startGame()
{
    logFile << "\n\n" << "NEW GAME" << "\n\n";

    placedSquares_.removeAllPlacedSquares();

    gameSpeedManager_.setGameSpeed();
    scoreManager_.restartScore();
    infoDisplayManager_.hideInfo();

    activeBlock_.reset();
    activeBlock_ = BlockBase::makeBlock();

    gameSpeedManager_.start();
    gameState_ = GameState::GameRunning;
}

void GameEngine::endGame()
{
    gameState_ = GameState::GameStopped;
    gameSpeedManager_.stop();

    qDebug() << "GAME OVER";
    infoDisplayManager_.setLabel("GAME OVER\nPRESS SPACE TO RESTART");
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
        if(activeBlock_->isSquareOrBottomWallUnderBlock(placedSquares_))
        {
            activeBlock_->placeBlock(placedSquares_);

            activeBlock_.reset();

            QVector<int> fullRows = placedSquares_.findFullRows();

            if(!fullRows.empty())
            {
                scoreManager_.rewardPlayerForFullRows(fullRows.size());

                for(auto row : fullRows)
                {
                    placedSquares_.removeFullRow(row);
                    placedSquares_.dropRowsAbove(row);
                }
            }

            activeBlock_ = BlockBase::makeBlock();

            if(activeBlock_->checkForOverlappingSquares(activeBlock_->getBlockCoordinates(), placedSquares_))
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

void GameEngine::processKey(QString key)
{
    if(gameState_ == GameState::GameRunning)
    {
        if(key == "left")
        {
            if(activeBlock_->checkMovePossibility(Direction::left, placedSquares_))
            {
                activeBlock_->moveBlock(Direction::left);
            }
        }
        else if(key == "right")
        {
            if(activeBlock_->checkMovePossibility(Direction::right, placedSquares_))
            {
                activeBlock_->moveBlock(Direction::right);
            }
        }
        else if(key == "up")
        {
            activeBlock_->rotateBlock(placedSquares_);
        }
        else if(key == "down")
        {
            activeBlock_->dropAndPlaceBlock(placedSquares_);
        }
        else if(key == "plus")
        {
            gameSpeedManager_.incrementSpeed();
        }
        else if(key == "minus")
        {
            gameSpeedManager_.decrementSpeed();
        }
        else if(key == "pause")
        {
            togglePause();
        }
    }
    else if(gameState_ == GameState::GameStopped)
    {
        if(key == "space")
        {
            startGame();
        }
    }
    else if(gameState_ == GameState::GamePaused)
    {
        if(key == "pause")
        {
            togglePause();
        }
    }
}
