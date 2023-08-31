#pragma once

#include "model/model.h"
#include <QWidget>

class GameArena : public QWidget
{
public:
    explicit GameArena(QWidget* parent, const Model& model);

private:
    void paintEvent(QPaintEvent*) override;

    void drawGameArena(QPainter& painter) const;
    void drawSquare(QPainter& painter, const Coordinates& coordinates) const;
    void drawBlock(QPainter& painter, const Block& block) const;
    void drawPlacedSquares(QPainter& painter, const PlacedSquares& placedSquares) const;

    [[maybe_unused]] void drawAllPossibleSquares(QPainter& painter);

    const Model& model_;
};
