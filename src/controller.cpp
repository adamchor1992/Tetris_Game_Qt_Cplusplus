#include "controller.h"
#include "block_movement_manager.h"

Controller::Controller(Model& model, MainWindow& view) : model_(model), view_(view)
{
    connect(&model_.getGameSpeedManager().getGameTickTimer(), &QTimer::timeout, this, &Controller::gameTickHandler);
    connect(view_.getSpeedHorizontalSlider(), &QSlider::valueChanged, this, &Controller::processSliderValueChanged);
    connect(&view_, &MainWindow::keyPressedEvent, this, &Controller::processKeyPressedEvent);

    view_.update();
    view_.updateInfoDisplay();
}

void Controller::processKeyPressedEvent(QKeyEvent* keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            if(model_.getGameStateManager().isRunning())
            {
                requestMoveActiveBlock(Direction::LEFT);
            }
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            if(model_.getGameStateManager().isRunning())
            {
                requestMoveActiveBlock(Direction::RIGHT);
            }
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            if(model_.getGameStateManager().isRunning())
            {
                requestRotateActiveBlock();
            }
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            if(model_.getGameStateManager().isRunning())
            {
                requestDropBlock();
            }
            break;

        case Qt::Key_Plus:
            requestIncrementGameSpeed();
            break;

        case Qt::Key_Minus:
            requestDecrementGameSpeed();
            break;

        case Qt::Key_P:
            requestTogglePause();
            break;

        case Qt::Key_Space:
            if(model_.getGameStateManager().isReadyToStart())
            {
                startGame();
            }
    }
}

void Controller::gameTickHandler()
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
        dropBlockOneRow();
    }
}

void Controller::startGame()
{
    model_.reset();

    generateNewBlock();

    model_.getGameStateManager().startGame();
    view_.updateInfoDisplay();
}

void Controller::endGame()
{
    model_.getGameStateManager().endGame();
    view_.updateInfoDisplay();
}

void Controller::dropBlockOneRow() const
{
    BlockMovementManager::lowerBlockOneRow(model_.getActiveBlockManager().getActiveBlock());
    view_.update();
}

void Controller::requestTogglePause()
{
    model_.getGameStateManager().togglePause();
    view_.updateInfoDisplay();
}

void Controller::processSliderValueChanged(int sliderValue)
{
    model_.getGameSpeedManager().setSpeedLevel(sliderValue);
}

void Controller::requestIncrementGameSpeed()
{
    model_.getGameSpeedManager().incrementSpeed();
    view_.getSpeedHorizontalSlider()->setValue(model_.getGameSpeedManager().getSpeedLevelInteger());
}

void Controller::requestDecrementGameSpeed()
{
    model_.getGameSpeedManager().decrementSpeed();
    view_.getSpeedHorizontalSlider()->setValue(model_.getGameSpeedManager().getSpeedLevelInteger());
}

void Controller::generateNewBlock()
{
    model_.getActiveBlockManager().createBlock();
    view_.update();
}

void Controller::requestMoveActiveBlock(Direction direction)
{
    BlockMovementSimulationResult blockMovementSimulationResult = BlockMovementManager::simulateHorizontalMove(model_.getActiveBlockManager().getActiveBlock(), direction, model_.getPlacedSquares());

    if(blockMovementSimulationResult.isValid())
    {
        BlockMovementManager::processMove(model_.getActiveBlockManager().getActiveBlock(), blockMovementSimulationResult);
        view_.update();
    }
}

void Controller::requestRotateActiveBlock()
{
    BlockRotationSimulationResult blockRotationSimulationResult = BlockMovementManager::simulateRotation(model_.getActiveBlockManager().getActiveBlock(), model_.getPlacedSquares());

    if(blockRotationSimulationResult.isValid())
    {
        BlockMovementManager::processRotation(model_.getActiveBlockManager().getActiveBlock(), blockRotationSimulationResult);
        view_.update();
    }
}

void Controller::requestDropBlock()
{
    BlockMovementManager::dropBlock(model_.getActiveBlockManager().getActiveBlock(), model_.getPlacedSquares());
    view_.update();
}

void Controller::handleFullRows()
{
    if(std::vector<int> fullRows = model_.getPlacedSquares().findFullRowsNumbers(); !fullRows.empty())
    {
        model_.getScoreManager().addRewardForFullRowsToScoreBalance(fullRows.size());

        for(int rowNumber : fullRows)
        {
            model_.getPlacedSquares().removeRow(rowNumber);
            model_.getPlacedSquares().dropRowsAboveGivenRow(rowNumber);
        }

        view_.update();
    }
}

void Controller::placeBlock()
{
    BlockMovementManager::placeBlock(model_.getActiveBlockManager().getActiveBlock(), model_.getPlacedSquares());
    view_.update();
}

bool Controller::isPlaceBlockConditionFulfilled()
{
    return BlockMovementManager::isSquareOrBottomWallUnderBlock(model_.getActiveBlockManager().getActiveBlock(), model_.getPlacedSquares());
}

bool Controller::isEndGameConditionFulfilled()
{
    return BlockMovementManager::checkForOverlappingSquares(model_.getActiveBlockManager().getActiveBlock(), model_.getPlacedSquares());
}
