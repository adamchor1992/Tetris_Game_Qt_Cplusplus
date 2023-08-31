#pragma once

#include "gtest/gtest.h"
#include <QColor>

class CommonTestFixture : public ::testing::Test
{
protected:
    const QColor DEFAULT_SQUARE_COLOR{Qt::green};
};
