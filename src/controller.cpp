#include "controller.h"
#include "log_manager.h"
#include "block_movement_manager.h"

Controller::Controller(Model* model, Window* view)
{
    model_ = model;
    view_ = view;
}

void Controller::subscribeToKeyEvents()
{
    connect(view_, &Window::keyPressedEvent, this, &Controller::processKeyPressedEvent);
}

void Controller::subscribeToGameTickTimer()
{
    connect(&model_->getGameSpeedManager()->getGameTickTimer(), &QTimer::timeout, this, &Controller::gameTickHandler);
}

void Controller::subscribeToSpeedSliderValueChangeEvent()
{
    connect(view_->getSpeedHorizontalSlider(), &QSlider::valueChanged, this, &Controller::processSliderValueChanged);
}

void Controller::processKeyPressedEvent(Key key)
{
    GameState gameState = model_->getGameState();

    if(gameState == GameState::Running)
    {
        if(key == Key::left)
        {
            moveActiveBlock(Direction::left);
        }
        else if(key == Key::right)
        {
            moveActiveBlock(Direction::right);
        }
        else if(key == Key::up)
        {
            rotateActiveBlock();
        }
        else if(key == Key::down)
        {
            dropActiveBlock();
        }
        else if(key == Key::plus)
        {
            incrementGameSpeed();
        }
        else if(key == Key::minus)
        {
            decrementGameSpeed();
        }
        else if(key == Key::pause)
        {
            togglePause();
        }
    }
    else if(gameState == GameState::BeforeFirstRun || gameState == GameState::Stopped)
    {
        if(key == Key::space)
        {
            startGame();
        }
    }
    else if(gameState == GameState::Paused)
    {
        if(key == Key::pause)
        {
            togglePause();
        }
    }
}

void Controller::gameTickHandler()
{
    if(model_->getGameState() == GameState::Running)
    {
        if(isPlaceBlockConditionFulfilled())
        {
            placeBlock();
            handleFullRows();
            generateNewBlock();

            if(isEndGameConditionFulfilled())
            {
                endGame();
            }
        }
        else
        {
            dropBlock();
        }
    }
}

void Controller::dropBlock() const
{
    model_->getActiveBlock()->dropBlockOneLevel();
}

void Controller::startGame()
{
    LOG(LogType::INFO) << "====================START GAME====================\n";

    if(model_->getGameState() != GameState::BeforeFirstRun)
    {
        model_->resetPlacedSquares();
    }

    resetScore();

    model_->getGameSpeedManager()->setSpeedLevel(model_->getGameSpeedManager()->getSpeedLevel());

    generateNewBlock();

    setGameState(GameState::Running);
}

void Controller::endGame()
{
    LOG(LogType::INFO) << "====================END GAME====================\n";
    setGameState(GameState::Stopped);
}

void Controller::togglePause()
{
    GameState gameState = model_->getGameState();

    if(gameState == GameState::Running)
    {
        pauseGame();
    }
    else if(gameState == GameState::Paused)
    {
        resumeGame();
    }
}

void Controller::initializeScore()
{
    view_->updateScore(model_->getScoreManager().getScore());
}

void Controller::prepareGameFirstRun()
{
    initializeScore();
    setGameState(GameState::BeforeFirstRun);
}

void Controller::processSliderValueChanged(int sliderValue)
{
    model_->getGameSpeedManager()->setSpeedLevel(sliderValue);
}

void Controller::incrementGameSpeed()
{
    model_->getGameSpeedManager()->incrementSpeed();
    view_->getSpeedHorizontalSlider()->setValue(model_->getGameSpeedManager()->getSpeedLevel());
}

void Controller::decrementGameSpeed()
{
    model_->getGameSpeedManager()->decrementSpeed();
    view_->getSpeedHorizontalSlider()->setValue(model_->getGameSpeedManager()->getSpeedLevel());
}

void Controller::resetScore()
{
    model_->resetScore();
}

void Controller::generateNewBlock()
{
    AbstractBlock* abstractBlock = model_->generateNewBlock();
    subscribeViewToUpdateBlockEvent(abstractBlock);
    view_->updateBlock(abstractBlock);
}

void Controller::moveActiveBlock(Direction direction)
{
    model_->getActiveBlock()->processMove(direction, *model_->getPlacedSquares());
}

void Controller::rotateActiveBlock()
{
    model_->getActiveBlock()->rotate(*model_->getPlacedSquares());
}

void Controller::dropActiveBlock()
{
    model_->getActiveBlock()->dropAndPlace(*model_->getPlacedSquares());
}

void Controller::handleFullRows()
{
    if(QVector<int> fullRows = model_->getPlacedSquares()->findFullRows(); !fullRows.empty())
    {
        model_->getScoreManager().rewardPlayerForFullRows(fullRows.size());

        for(int rowNumber : fullRows)
        {
            model_->getPlacedSquares()->removeRow(rowNumber);
            model_->getPlacedSquares()->dropRowsAboveRow(rowNumber);
        }
    }
}

void Controller::subscribeViewToUpdateBlockEvent(AbstractBlock* abstractBlock)
{
    connect(abstractBlock, &AbstractBlock::blockUpdatedEvent, view_, &Window::updateBlock);
}

void Controller::subscribeViewToPlacedSquaresChangesEvent()
{
    connect(model_->getPlacedSquares().get(), &PlacedSquares::placedSquaresUpdatedEvent, view_, &Window::updatePlacedSquares);
}

void Controller::subscribeViewToUpdateScoreEvent()
{
    connect(&model_->getScoreManager(), &ScoreManager::scoreUpdatedEvent, view_, &Window::updateScore);
}

void Controller::resumeGame()
{
    setGameState(GameState::Running);
}

void Controller::pauseGame()
{
    setGameState(GameState::Paused);
}

void Controller::placeBlock()
{
    model_->getActiveBlock()->place(*model_->getPlacedSquares());
}

bool Controller::isEndGameConditionFulfilled()
{
    return BlockMovementManager::checkForOverlappingSquares(model_->getActiveBlock()->getSquaresCoordinates(), *model_->getPlacedSquares());
}

bool Controller::isPlaceBlockConditionFulfilled()
{
    return model_->getActiveBlock()->isSquareOrBottomWallUnderBlock(*model_->getPlacedSquares());
}

void Controller::setGameState(GameState gameState)
{
    model_->setGameState(gameState);

    if(gameState == GameState::BeforeFirstRun)
    {
        view_->updateInfoDisplay(InfoDisplayOptions::FIRST_START_INFO);
    }
    else if(gameState == GameState::Stopped)
    {
        model_->getGameSpeedManager()->stop();
        view_->updateInfoDisplay(InfoDisplayOptions::RESTART_INFO);
    }
    else if(gameState == GameState::Running)
    {
        model_->getGameSpeedManager()->start();
        view_->updateInfoDisplay(InfoDisplayOptions::NO_INFO);
    }
    else if(gameState == GameState::Paused)
    {
        model_->getGameSpeedManager()->stop();
        view_->updateInfoDisplay(InfoDisplayOptions::PAUSED_INFO);
    }
    else
    {
        throw std::runtime_error("Unsupported game state");
    }
}
