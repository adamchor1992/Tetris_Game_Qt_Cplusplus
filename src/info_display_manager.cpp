#include "info_display_manager.h"

InfoDisplayManager::InfoDisplayManager()
{
    setLabel(startText);
}

void InfoDisplayManager::connectInfoLabel(QLabel* infoLabel)
{
    infoLabel_ = infoLabel;
}

void InfoDisplayManager::hideInfo()
{
    infoLabel_->hide();
}

void InfoDisplayManager::showRestartInfo()
{
    setLabel(restartText);
}

void InfoDisplayManager::setLabel(const QString& text)
{
    infoLabel_->setText(text);
    infoLabel_->show();
}
