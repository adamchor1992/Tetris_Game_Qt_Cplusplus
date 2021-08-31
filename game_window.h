#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "game_engine.h"

namespace Ui
{
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow() override;

private:
    Ui::GameWindow* m_pUi = nullptr;
    QGraphicsScene m_Scene;
    std::unique_ptr<GameEngine> m_GameEngine;

    void InitializeGameplayAreaScene();
    void keyPressEvent(QKeyEvent *event) override;
};
