#pragma once

#include <QLabel>

class InfoDisplayManager
{
public:
    InfoDisplayManager();
    static void connectInfoLabel(QLabel* infoLabel);
    void hideInfo();
    void setLabel(QString text);

private:
    static QLabel* infoLabel_;
};
