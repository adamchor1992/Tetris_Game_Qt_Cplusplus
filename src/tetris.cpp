#include "tetris.h"

Tetris::Tetris()
{
    model_ = std::make_unique<Model>();
    view_ = std::make_unique<Window>();
    controller_ = std::make_unique<Controller>(model_.get(), view_.get());

    controller_->prepareGameFirstRun();

    view_->show();

    controller_->subscribeViewToUpdateScoreEvent();
    controller_->subscribeViewToPlacedSquaresChangesEvent();
    controller_->subscribeToGameTickTimer();
    controller_->subscribeToSpeedSliderValueChangeEvent();
    controller_->subscribeToKeyEvents();
}
