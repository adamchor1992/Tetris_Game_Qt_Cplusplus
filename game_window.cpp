#include "game_window.h"
#include "ui_game_window.h"
#include <map>
#include "drawer.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_pUi(new Ui::GameWindow)
{
    m_pUi->setupUi(this);

    m_ScoreManager.ConnectScoreLabel(m_pUi->m_ScoreDisplayLabel);

    setWindowTitle("Tetris");
    setFocus(Qt::ActiveWindowFocusReason);

    Drawer::SetScene(&m_Scene);

    InitializeGameplayAreaScene();
    Drawer::DrawGameArena();

    m_GameState = GameState::GameStopped;

    SetInformationLabel("PRESS SPACE TO START");

    connect(&m_GameTickTimer, &QTimer::timeout, this, &GameWindow::GameTickHandler);
}

void GameWindow::InitializeGameplayAreaScene()
{
    const int sceneX = 0;
    const int sceneY = 0;
    const int sceneWidth = m_pUi->m_GraphicsView->geometry().width();
    const int sceneHeight = m_pUi->m_GraphicsView->geometry().height();

    m_pUi->m_GraphicsView->setScene(&m_Scene);
    m_pUi->m_GraphicsView->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeight);

    qDebug("Gameplay scene initialized");
}

void GameWindow::StartGame()
{
    m_PlacedSquares.RemoveAllPlacedSquares();

    SetGameSpeedLevel(m_pUi->m_SpeedHorizontalSlider->value());
    m_ScoreManager.RestartScore();
    m_pUi->m_InfoDisplayLabel->hide();
    m_pActiveBlock.reset();
    m_pActiveBlock = BlockBase::MakeBlock();

    m_GameTickTimer.start();
    m_GameState = GameState::GameRunning;
}

void GameWindow::EndGame()
{
    m_GameState = GameState::GameStopped;
    m_GameTickTimer.stop();

    qDebug() << "GAME OVER";
    SetInformationLabel("GAME OVER\nPRESS SPACE TO RESTART");
}

GameWindow::~GameWindow()
{
    delete m_pUi;
}

void GameWindow::TogglePause()
{
    if(m_GameState == GameState::GameRunning)
    {
        qDebug() << "Pause";
        m_GameTickTimer.stop();
        m_GameState = GameState::GamePaused;
    }
    else if(m_GameState == GameState::GamePaused)
    {
        qDebug() << "Unpause";
        m_GameTickTimer.start();
        m_GameState = GameState::GameRunning;
    }
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    int sliderValue = m_pUi->m_SpeedHorizontalSlider->value();

    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_A:
        if(m_GameState == GameState::GameRunning)
        {
            if(m_pActiveBlock->CheckMovePossibility(Direction::left, m_PlacedSquares))
            {
                m_pActiveBlock->MoveBlock(Direction::left);
            }
        }
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        if(m_GameState == GameState::GameRunning)
        {
            if(m_pActiveBlock->CheckMovePossibility(Direction::right, m_PlacedSquares))
            {
                m_pActiveBlock->MoveBlock(Direction::right);
            }
        }
        break;

    case Qt::Key_Up:
    case Qt::Key_W:
        if(m_GameState == GameState::GameRunning)
        {
            m_pActiveBlock->RotateBlock(m_PlacedSquares);
        }
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        if(m_GameState == GameState::GameRunning)
        {
            m_pActiveBlock->DropAndPlaceBlock(m_PlacedSquares);
            qDebug() << "Drop";
        }
        break;

    case Qt::Key_Plus:
        /*Subtracting means increasing speed*/
        m_pUi->m_SpeedHorizontalSlider->setValue(sliderValue - 1);
        break;

    case Qt::Key_Minus:
        /*Adding means decreasing speed*/
        m_pUi->m_SpeedHorizontalSlider->setValue(sliderValue + 1);
        break;

    case Qt::Key_P:
        TogglePause();
        break;

    case Qt::Key_Space:
        if(m_GameState == GameState::GameStopped)
        {
            qDebug() << "Start game";
            StartGame();
        }
        break;

    default:
        qDebug() << "Unknown key";
    }
}

void GameWindow::SetInformationLabel(QString text)
{
    m_pUi->m_InfoDisplayLabel->setText(text);
    m_pUi->m_InfoDisplayLabel->show();
}

void GameWindow::SetGameSpeedLevel(int speedLevel)
{
    const int TIME_OFFSET = 50;

    m_GameTickTimer.setInterval(TIME_OFFSET + speedLevel * 20);
}

void GameWindow::on_m_SpeedHorizontalSlider_valueChanged(int value)
{
    SetGameSpeedLevel(value);
}

void GameWindow::GameTickHandler()
{
    if(m_GameState == GameState::GameRunning)
    {
        /*Check if there is floor or other square under any of block squares*/
        if(m_pActiveBlock->IsSquareOrBottomWallUnderBlock(m_PlacedSquares))
        {
            m_pActiveBlock->PlaceBlock(m_PlacedSquares);

            m_pActiveBlock.reset();

            QVector<int> fullRows = m_PlacedSquares.FindFullRows();

            if(!fullRows.empty())
            {
                m_ScoreManager.RewardPlayerForFullRows(fullRows.size());

                for(auto row : fullRows)
                {
                    m_PlacedSquares.RemoveFullRow(row);
                    m_PlacedSquares.DropRowsAbove(row);
                }
            }

            m_pActiveBlock = BlockBase::MakeBlock();

            if(m_pActiveBlock->CheckForOverlappingSquares(m_pActiveBlock->GetBlockCoordinates(), m_PlacedSquares))
            {
                EndGame();
            }
        }

        else
        {
            m_pActiveBlock->DropBlockOneLevel();
        }
    }
}
