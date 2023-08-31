#include "main_window.h"
#include "ui_main_window.h"

MainWindow::MainWindow(const Model& model) : QMainWindow(), model_(model), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    setWindowTitle("Tetris");
    setFocus(Qt::ActiveWindowFocusReason);

    gameArena_ = std::make_unique<GameArena>(this->centralWidget(), model);
    gameArena_->setFixedSize(310, 610);
    gameArena_->setGeometry(QRect(20, 20, 350, 650));

    setFixedSize(size());

    centerOnScreen();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::centerOnScreen()
{
    const QRect screenRect = QWidget::screen()->availableGeometry();
    const QRect widgetRect({}, frameSize().boundedTo(screenRect.size()));

    move(screenRect.center() - widgetRect.center());
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    emit keyPressedEvent(event);
}

void MainWindow::updateInfoDisplay()
{
    ui_->info_display_label->setText(model_.getGameStateManager().getCurrentStateInfoText());
}

void MainWindow::update()
{
    QWidget::update();
    updateScore();
}

void MainWindow::updateScore()
{
    ui_->score_display_label->setText(model_.getScoreManager().getScoreInfoText());
}

QSlider* MainWindow::getSpeedHorizontalSlider() const
{
    return ui_->speed_horizontal_slider;
}
