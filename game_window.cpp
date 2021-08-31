#include "game_window.h"
#include "ui_game_window.h"
#include "drawer.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), m_pUi(new Ui::GameWindow)
{
    m_pUi->setupUi(this);
    setWindowTitle("Tetris");
    setFocus(Qt::ActiveWindowFocusReason);

    ScoreManager::ConnectScoreLabel(m_pUi->m_ScoreDisplayLabel);
    InfoDisplayManager::ConnectInfoLabel(m_pUi->m_InfoDisplayLabel);
    GameSpeedManager::ConnectSpeedSlider(m_pUi->m_SpeedHorizontalSlider);

    InitializeGameplayAreaScene();
    Drawer::DrawGameArena();

    m_GameEngine = std::make_unique<GameEngine>();
}

void GameWindow::InitializeGameplayAreaScene()
{
    const int sceneX = 0;
    const int sceneY = 0;
    const int sceneWidth = m_pUi->m_GraphicsView->geometry().width();
    const int sceneHeight = m_pUi->m_GraphicsView->geometry().height();

    m_pUi->m_GraphicsView->setScene(&m_Scene);
    m_pUi->m_GraphicsView->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeight);

    Drawer::SetScene(&m_Scene);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_A:
        m_GameEngine->ProcessKey("left");
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        m_GameEngine->ProcessKey("right");
        break;

    case Qt::Key_Up:
    case Qt::Key_W:
        m_GameEngine->ProcessKey("up");
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        m_GameEngine->ProcessKey("down");
        break;

    case Qt::Key_Plus:
        m_GameEngine->ProcessKey("plus");
        break;

    case Qt::Key_Minus:
        m_GameEngine->ProcessKey("minus");
        break;

    case Qt::Key_P:
        m_GameEngine->ProcessKey("pause");
        break;

    case Qt::Key_Space:
        m_GameEngine->ProcessKey("space");
        break;

    default:
        qDebug() << "Unknown key";
    }
}

GameWindow::~GameWindow()
{
    delete m_pUi;
}
