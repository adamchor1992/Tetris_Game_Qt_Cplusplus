#include "game_window.h"
#include "ui_game_window.h"
#include "drawer.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), ui_(new Ui::GameWindow)
{
    ui_->setupUi(this);
    setWindowTitle("Tetris");
    setFocus(Qt::ActiveWindowFocusReason);

    ScoreManager::connectScoreLabel(ui_->score_display_label);
    InfoDisplayManager::connectInfoLabel(ui_->info_display_label);
    GameSpeedManager::connectSpeedSlider(ui_->speed_horizontal_slider);

    initializeGameplayAreaScene();
    Drawer::drawGameArena();

    gameEngine_ = std::make_unique<GameEngine>();
}

void GameWindow::initializeGameplayAreaScene()
{
    const int sceneX = 0;
    const int sceneY = 0;
    const int sceneWidth = ui_->graphics_view->geometry().width();
    const int sceneHeight = ui_->graphics_view->geometry().height();

    ui_->graphics_view->setScene(&scene_);
    ui_->graphics_view->setSceneRect(sceneX, sceneY, sceneWidth, sceneHeight);

    Drawer::setScene(&scene_);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
    case Qt::Key_A:
        gameEngine_->processKey("left");
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        gameEngine_->processKey("right");
        break;

    case Qt::Key_Up:
    case Qt::Key_W:
        gameEngine_->processKey("up");
        break;

    case Qt::Key_Down:
    case Qt::Key_S:
        gameEngine_->processKey("down");
        break;

    case Qt::Key_Plus:
        gameEngine_->processKey("plus");
        break;

    case Qt::Key_Minus:
        gameEngine_->processKey("minus");
        break;

    case Qt::Key_P:
        gameEngine_->processKey("pause");
        break;

    case Qt::Key_Space:
        gameEngine_->processKey("space");
        break;

    default:
        qDebug() << "Unknown key";
    }
}

GameWindow::~GameWindow()
{
    delete ui_;
}
