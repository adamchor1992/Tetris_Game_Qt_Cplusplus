#pragma once

#include <QLabel>

class InfoDisplayManager
{
public:
    InfoDisplayManager();
    static void ConnectInfoLabel(QLabel* scoreLabel);
    void HideInfo();
    void SetLabel(QString text);

private:
    static QLabel* m_InfoLabel;
};
