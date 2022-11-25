#pragma once

#include "ui_window.h"
#include "game_arena.h"

#include <QKeyEvent>

namespace Ui
{
    class Window;
}

class Window : public QMainWindow
{
Q_OBJECT

signals:
    void keyPressedEvent(Key key);

public slots:
    void updatePlacedSquares(PlacedSquares* placedSquares);
    void updateBlock(AbstractBlock* abstractBlock);
    void updateScore(int score);

public:
    explicit Window();
    ~Window() override;

    [[nodiscard]] QSlider* getSpeedHorizontalSlider() const
    { return ui_->speed_horizontal_slider; }

    void updateInfoDisplay(const QString& text);

private:
    void keyPressEvent(QKeyEvent* event) override;

    Ui::Window* ui_;
    GameArena* gameArena_;
};
