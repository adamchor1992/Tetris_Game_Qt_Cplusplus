#pragma once

#include <QLabel>

class InfoDisplayManager
{
public:
    InfoDisplayManager();

    static void connectInfoLabel(QLabel* infoLabel);

    void hideInfo();
    void showRestartInfo();

private:
    inline static QLabel* infoLabel_ = nullptr;

    const QString startText{"PRESS SPACE TO START"};
    const QString restartText{"GAME OVER\nPRESS SPACE TO RESTART"};

    void setLabel(const QString& text);
};
