#pragma once

#include "model/model.h"
#include "frontend/main_window.h"

class Controller : public QObject
{
Q_OBJECT

public slots:
    void processKeyPressedEvent(QKeyEvent* keyEvent);
    void gameTickHandler();
    void processSliderValueChanged(int sliderValue);

public:
    Controller(Model& model, MainWindow& view);

private:
    void startGame();
    void endGame();
    void requestTogglePause();

    void requestIncrementGameSpeed();
    void requestDecrementGameSpeed();

    void generateNewBlock();

    void requestMoveActiveBlock(Direction direction);
    void requestRotateActiveBlock();
    void requestDropBlock();
    void handleFullRows();
    void placeBlock();
    bool isEndGameConditionFulfilled();
    void dropBlockOneRow() const;
    bool isPlaceBlockConditionFulfilled();

    Model& model_;
    MainWindow& view_;
};
