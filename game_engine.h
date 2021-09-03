#pragma once

#include "block_base.h"
#include "placed_squares.h"
#include "random_number_generator.h"
#include "score_manager.h"
#include "info_display_manager.h"
#include "game_speed_manager.h"

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine();
    void processKey(QString key);

private:
    void placeBlock();
    void findAndDeleteFullRows();
    void startGame();
    void endGame();
    void togglePause();

    enum class GameState
    {
        GameRunning,
        GamePaused,
        GameStopped
    };

    PlacedSquares placedSquares_;
    ScoreManager scoreManager_;
    InfoDisplayManager infoDisplayManager_;
    GameSpeedManager gameSpeedManager_;
    std::unique_ptr<BlockBase> activeBlock_;
    GameState gameState_;

private slots:
    void gameTickHandler();
};
