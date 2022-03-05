#pragma once

#include <QLabel>

class InfoDisplayManager
{
public:
    InfoDisplayManager();
    static void connectInfoLabel(QLabel* infoLabel);
    void hideInfo();
    void setLabel(const QString& text);

private:
    inline static QLabel* infoLabel_ = nullptr;
};
