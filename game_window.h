#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <random>

#include "block_base.h"
#include "drawer.h"
#include "placed_blocks.h"
#include "blocks/i_block.h"
#include "blocks/i_block.h"
#include "blocks/s_block.h"
#include "blocks/z_block.h"
#include "blocks/j_block.h"
#include "blocks/l_block.h"
#include "blocks/o_block.h"
#include "blocks/t_block.h"

namespace Ui
{
    class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void GameTick();

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow() override;

private:
    Ui::GameWindow* m_pUi = nullptr;
    QGraphicsScene m_Scene;
    Drawer m_Drawer;
    PlacedBlocks m_PlacedBlocks;

    QTimer m_GameTickTimer;

    BlockBase* m_pCurrentBlock = nullptr;

    int m_Score;

    enum class GameState
    {
        BeforeFirstRun,
        GameRunning,
        GamePaused,
        GameStopped
    };

    GameState m_GameState;

    void InitializeGameplayAreaScene();
    void DrawGameArena();
    void PrepareFirstGameRun();
    void GenerateInitialBlock();
    void DrawAllPossibleSquares();
    BlockBase* GenerateBlock(QString shape = "random");
    void PlaceBlock();
    void FindAndDeleteFullRows();
    void RedrawMovedBlock();
    void RedrawDroppedBlock();
    void PlaceCurrentBlock();
    void EndGame();
    void StartGame();
    void RestartGame();
    void SetScore(int score) {m_Score = score;}
    void IncreaseScore(int score) {m_Score += score;}
    void UpdateScoreLabel();
    void SetInformationLabel(QString text);

    void keyPressEvent(QKeyEvent *event) override;
};
