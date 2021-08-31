#include "info_display_manager.h"

QLabel* InfoDisplayManager::m_InfoLabel = nullptr;

InfoDisplayManager::InfoDisplayManager()
{
    SetLabel("PRESS SPACE TO START");
}

void InfoDisplayManager::ConnectInfoLabel(QLabel* infoLabel)
{
    m_InfoLabel = infoLabel;
}

void InfoDisplayManager::HideInfo()
{
    m_InfoLabel->hide();
}

void InfoDisplayManager::SetLabel(QString text)
{
    m_InfoLabel->setText(text);
    m_InfoLabel->show();
}
