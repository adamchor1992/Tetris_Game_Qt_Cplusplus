#pragma once

#include "block_factory.h"
#include "block_base.h"
#include "placed_squares.h"
#include "random_generator.h"
#include "score_manager.h"
#include "info_display_manager.h"
#include "game_speed_manager.h"

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine();
    void processKey(Key key);

private:
    void startGame();
    void endGame();
    void togglePause();

    enum class GameState
    {
        Running,
        Paused,
        Stopped
    };

    std::unique_ptr<PlacedSquares> placedSquares_;
    std::unique_ptr<ScoreManager> scoreManager_;
    InfoDisplayManager infoDisplayManager_;
    GameSpeedManager gameSpeedManager_;
    BlockFactory blockFactory_;
    std::unique_ptr<BlockBase> activeBlock_;
    GameState gameState_;

private slots:
    void gameTickHandler();
};
