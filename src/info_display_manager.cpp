#include "info_display_manager.h"

InfoDisplayManager::InfoDisplayManager()
{
    setLabel("PRESS SPACE TO START");
}

void InfoDisplayManager::connectInfoLabel(QLabel* infoLabel)
{
    infoLabel_ = infoLabel;
}

void InfoDisplayManager::hideInfo()
{
    infoLabel_->hide();
}

void InfoDisplayManager::setLabel(const QString& text)
{
    infoLabel_->setText(text);
    infoLabel_->show();
}
