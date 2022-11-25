#pragma once

#include "model.h"
#include "view/window.h"
#include "controller.h"

class Tetris
{
public:
    Tetris();

private:
    std::unique_ptr<Model> model_;
    std::unique_ptr<Window> view_;
    std::unique_ptr<Controller> controller_;
};
