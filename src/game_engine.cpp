#include "game_engine.h"
#include "log_manager.h"

GameEngine::GameEngine()
{
    gameState_ = GameState::Stopped;
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

    activeBlock_ = blockFactory_.makeRandomBlock();

    gameSpeedManager_.start();
    gameState_ = GameState::Running;
}

void GameEngine::endGame()
{
    logFile << "\n\nEND GAME\n\n";
    logFile << "====================";

    gameState_ = GameState::Stopped;
    gameSpeedManager_.stop();
    infoDisplayManager_.showRestartInfo();
}

void GameEngine::togglePause()
{
    if(gameState_ == GameState::Running)
    {
        gameSpeedManager_.stop();
        gameState_ = GameState::Paused;
    }
    else if(gameState_ == GameState::Paused)
    {
        gameSpeedManager_.start();
        gameState_ = GameState::Running;
    }
}

void GameEngine::gameTickHandler()
{
    if(gameState_ == GameState::Running)
    {
        if(activeBlock_->isSquareOrBottomWallUnderBlock(*placedSquares_))
        {
            activeBlock_->placeBlock(*placedSquares_);

            if(QVector<int> fullRows = placedSquares_->findFullRows(); !fullRows.empty())
            {
                scoreManager_->rewardPlayerForFullRows(fullRows.size());

                for(int rowNumber : fullRows)
                {
                    placedSquares_->removeRow(rowNumber);
                    placedSquares_->dropRowsAboveRow(rowNumber);
                }
            }

            activeBlock_ = blockFactory_.makeRandomBlock();

            if(activeBlock_->checkForOverlappingSquares(activeBlock_->extractAllSquareCoordinates(), *placedSquares_))
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
    if(gameState_ == GameState::Running)
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
    else if(gameState_ == GameState::Stopped)
    {
        if(key == Key::space)
        {
            startGame();
        }
    }
    else if(gameState_ == GameState::Paused)
    {
        if(key == Key::pause)
        {
            togglePause();
        }
    }
}
