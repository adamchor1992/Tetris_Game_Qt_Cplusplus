#pragma once

#include "model.h"
#include "view/window.h"

class Controller : public QObject
{
Q_OBJECT

public slots:
    void processKeyPressedEvent(Key key);
    void gameTickHandler();
    void processSliderValueChanged(int sliderValue);

public:
    Controller(Model* model, Window* view);
    void prepareGameFirstRun();
    void subscribeViewToPlacedSquaresChangesEvent();
    void subscribeToGameTickTimer();
    void subscribeToSpeedSliderValueChangeEvent();
    void subscribeToKeyEvents();
    void subscribeViewToUpdateScoreEvent();

private:
    void initializeScore();
    void startGame();
    void endGame();
    void togglePause();

    void incrementGameSpeed();
    void decrementGameSpeed();

    void generateNewBlock();

    void subscribeViewToUpdateBlockEvent(AbstractBlock* abstractBlock);

    void resetScore();
    void moveActiveBlock(Direction direction);
    void rotateActiveBlock();
    void dropActiveBlock();
    void handleFullRows();
    void resumeGame();
    void pauseGame();
    void placeBlock();
    bool isEndGameConditionFulfilled();
    void dropBlock() const;
    bool isPlaceBlockConditionFulfilled();

    void setGameState(GameState gameState);

    Model* model_;
    Window* view_;
};
