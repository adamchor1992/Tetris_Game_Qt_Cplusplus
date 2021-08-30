#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <memory>

#include "block_base.h"
#include "placed_squares.h"
#include "random_number_generator.h"
#include "score_manager.h"

namespace Ui
{
    class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void GameTickHandler();

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow() override;

private slots:
    void on_m_SpeedHorizontalSlider_valueChanged(int value);

private:
    Ui::GameWindow* m_pUi = nullptr;
    QGraphicsScene m_Scene;
    PlacedSquares m_PlacedSquares;

    QTimer m_GameTickTimer;
    ScoreManager m_ScoreManager;

    std::unique_ptr<BlockBase> m_pActiveBlock;

    enum class GameState
    {
        GameRunning,
        GamePaused,
        GameStopped
    };

    GameState m_GameState;

    void InitializeGameplayAreaScene();
    void DrawAllPossibleSquares();
    void PlaceBlock();
    void FindAndDeleteFullRows();
    void StartGame();
    void EndGame();
    void SetInformationLabel(QString text);
    void SetGameSpeedLevel(int speedLevel);

    void keyPressEvent(QKeyEvent *event) override;
    void TogglePause();
};
