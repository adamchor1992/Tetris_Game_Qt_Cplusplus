#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <random>

#include "block.h"
#include "drawer.h"
#include "placed_blocks.h"
#include "i_block.h"
#include "s_block.h"
#include "z_block.h"
#include "j_block.h"
#include "l_block.h"
#include "o_block.h"
#include "t_block.h"

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
    Block* m_pCurrentBlock = nullptr;
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
