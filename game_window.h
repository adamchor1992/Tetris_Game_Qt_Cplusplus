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
    Ui::GameWindow *ui = nullptr;
    QGraphicsScene m_Scene;
    QTimer m_DropTimer;
    QGraphicsRectItem* m_pSquare = nullptr;
    Drawer* m_pDrawer = nullptr;
    BlockBase* m_pCurrentBlock = nullptr;
    QVector<QGraphicsRectItem*> m_CurrentBlockGraphicsItemsPtrs;
    PlacedBlocks* m_pPlacedBlocks = nullptr;
    int m_Score = 0;

    enum class GameState
    {
        BeforeFirstRun,
        GameRunning,
        GamePaused,
        GameStopped
    };

    GameState m_GameState;

    struct GameArenaParameters
    {
        static int const leftBorderX = 0;
        static int const leftBorderXOffset = +2;
        static int const rightBorderX = 305;
        static int const rightBorderXOffset = +2;
        static int const bottomY = 610;
        static int const bottomYOffset = -3;
        static int const topY = 0;
        static int const topYOffset = +2;

        static int const MAX_BLOCK_ROWS = 20;
        static int const MAX_BLOCK_COLUMNS = 10;
        static int const BLOCK_SQUARE_SIZE = 30;
    };

    //GameArenaParameters m_GameArena;
    //GameArenaParameters m_GameArena2;

    void InitializeGameplayAreaScene();
    void DrawGameArena();
    void PrepareFirstGameRun();
    void DrawAllPossibleSquares();
    void GenerateBlock(QString shape = "0"); //if no argument, then generate random shape
    void GenerateRandomBlock();
    void PlaceBlock();
    void FindAndDeleteFullRows();
    void RedrawBlock();
    void PlaceCurrentBlock();
    void EndGame();
    void StartGame();
    void RestartGame();

    void keyPressEvent(QKeyEvent *event) override;
};
