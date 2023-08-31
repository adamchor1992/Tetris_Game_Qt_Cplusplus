#pragma once

#include "game_arena.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QSlider>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

signals:
    void keyPressedEvent(QKeyEvent* event);

public:
    explicit MainWindow(const Model& model);
    ~MainWindow() override;
    void update();

    [[nodiscard]] QSlider* getSpeedHorizontalSlider() const;

    void updateInfoDisplay();

private:
    void keyPressEvent(QKeyEvent* event) override;
    void centerOnScreen();
    void updateScore();

    Ui::MainWindow* ui_;
    std::unique_ptr<GameArena> gameArena_;
    const Model& model_;
};
