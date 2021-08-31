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
    void ProcessKey(QString key);

public slots:
    void GameTickHandler();

private:
    PlacedSquares m_PlacedSquares;

    ScoreManager m_ScoreManager;
    InfoDisplayManager m_InfoDisplayManager;
    GameSpeedManager m_GameSpeedManager;

    std::unique_ptr<BlockBase> m_pActiveBlock;

    enum class GameState
    {
        GameRunning,
        GamePaused,
        GameStopped
    };

    GameState m_GameState;

    void PlaceBlock();
    void FindAndDeleteFullRows();
    void StartGame();
    void EndGame();
    void TogglePause();
};
