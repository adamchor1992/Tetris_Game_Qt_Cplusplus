#pragma once

#include "abstract_block.h"
#include "placed_squares.h"

#include <QWidget>

class GameArena : public QWidget
{
public:
    explicit GameArena(QWidget* parent);
    void paintEvent([[maybe_unused]] QPaintEvent* event) override;
    void updateBlock(AbstractBlock* abstractBlock);
    void updatePlacedSquares(PlacedSquares* placedSquares);

private:
    void drawGameArena(QPainter& painter) const;
    void drawBlock(QPainter& painter) const;
    void drawPlacedSquares(QPainter& painter) const;

    AbstractBlock* abstractBlock_{};
    PlacedSquares* placedSquares_{};
};
