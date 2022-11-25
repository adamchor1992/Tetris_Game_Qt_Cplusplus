#include "view/window.h"

Window::Window() : QMainWindow(), ui_(new Ui::Window)
{
    ui_->setupUi(this);
    setWindowTitle("Tetris");
    setFocus(Qt::ActiveWindowFocusReason);

    gameArena_ = new GameArena(this->centralWidget());

    gameArena_->setFixedSize(310, 610);
    gameArena_->setGeometry(QRect(20, 20, 350, 650));
}

Window::~Window()
{
    delete gameArena_;
    delete ui_;
}

void Window::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Left:
        case Qt::Key_A:
            emit keyPressedEvent(Key::left);
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            emit keyPressedEvent(Key::right);
            break;

        case Qt::Key_Up:
        case Qt::Key_W:
            emit keyPressedEvent(Key::up);
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            emit keyPressedEvent(Key::down);
            break;

        case Qt::Key_Plus:
            emit keyPressedEvent(Key::plus);
            break;

        case Qt::Key_Minus:
            emit keyPressedEvent(Key::minus);
            break;

        case Qt::Key_P:
            emit keyPressedEvent(Key::pause);
            break;

        case Qt::Key_Space:
            emit keyPressedEvent(Key::space);
            break;
    }
}

void Window::updateInfoDisplay(const QString& text)
{
    ui_->info_display_label->setText(text);
}

void Window::updateBlock(AbstractBlock* abstractBlock)
{
    gameArena_->updateBlock(abstractBlock);
}

void Window::updatePlacedSquares(PlacedSquares* placedSquares)
{
    gameArena_->updatePlacedSquares(placedSquares);
}

void Window::updateScore(int score)
{
    ui_->score_display_label->setText("SCORE: " + QString::number(score));
}
