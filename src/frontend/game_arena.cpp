#include "game_arena.h"
#include "gui_config.h"
#include <QPainter>

using namespace GuiConfig::GameArenaParameters;
using namespace GuiConfig::Square;

GameArena::GameArena(QWidget* parent, const Model& model) : QWidget(parent), model_(model)
{}

void GameArena::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawGameArena(painter);

    if(model_.getActiveBlockManager().blockExists())
    {
        drawBlock(painter, model_.getActiveBlockManager().getActiveBlock());
    }

    drawPlacedSquares(painter, model_.getPlacedSquares());
}

void GameArena::drawGameArena(QPainter& painter) const
{
    QBrush brush(Edge::COLOR);
    QPen pen(brush, Edge::THICKNESS);

    painter.setBrush(brush);
    painter.setPen(pen);

    auto drawLeftEdge = [](QPainter& painter)
    {
        painter.drawLine(LeftEdge::X + LeftEdge::OFFSET_X, BottomEdge::Y, LeftEdge::X + LeftEdge::OFFSET_X, TopEdge::Y);
    };

    auto drawRightEdge = [](QPainter& painter)
    {
        painter.drawLine(RightEdge::X + RightEdge::OFFSET_X, BottomEdge::Y, RightEdge::X + RightEdge::OFFSET_X, TopEdge::Y);
    };

    auto drawBottomEdge = [](QPainter& painter)
    {
        painter.drawLine(LeftEdge::X, BottomEdge::Y + BottomEdge::OFFSET_Y, RightEdge::X, BottomEdge::Y + BottomEdge::OFFSET_Y);
    };

    auto drawTopEdge = [](QPainter& painter)
    {
        painter.drawLine(LeftEdge::X, TopEdge::Y + TopEdge::OFFSET_Y, RightEdge::X, TopEdge::Y + TopEdge::OFFSET_Y);
    };

    drawLeftEdge(painter);
    drawRightEdge(painter);
    drawBottomEdge(painter);
    drawTopEdge(painter);
}

void GameArena::drawSquare(QPainter& painter, const Coordinates& coordinates) const
{
    painter.drawRoundedRect((coordinates.x - 1) * SIZE + OFFSET, (coordinates.y - 1) * SIZE + OFFSET, SIZE, SIZE, ROUNDED_RECT_RATIO_PERCENTAGE, ROUNDED_RECT_RATIO_PERCENTAGE, Qt::RelativeSize);
}

void GameArena::drawBlock(QPainter& painter, const Block& block) const
{
    painter.setBrush(block.getColor());
    painter.setPen(Qt::NoPen);

    for(const Coordinates& coordinates : block.getAllSquaresCoordinates())
    {
        drawSquare(painter, coordinates);
    }
}

void GameArena::drawPlacedSquares(QPainter& painter, const PlacedSquares& placedSquares) const
{
    for(const auto&[coordinates, square] : placedSquares.getCoordinatesToSquaresMapping())
    {
        const QPen pen(Qt::NoPen);
        const QBrush brush(square.getColor());

        painter.setPen(pen);
        painter.setBrush(brush);

        drawSquare(painter, coordinates);
    }
}

[[maybe_unused]] void GameArena::drawAllPossibleSquares(QPainter& painter)
{
    static const QBrush redBrush(Qt::red);
    static const QBrush greenBrush(Qt::green);

    painter.setPen(Qt::NoPen);

    for(int x = Config::Arena::MINIMUM_X; x <= Config::Arena::MAXIMUM_X; ++x)
    {
        for(int y = Config::Arena::MINIMUM_Y; y <= Config::Arena::MAXIMUM_Y; ++y)
        {
            if(x % 2 == 0)
            {
                if(y % 2 == 0)
                {
                    painter.setBrush(redBrush);
                }
                else
                {
                    painter.setBrush(greenBrush);
                }
            }
            else
            {
                if(y % 2 == 0)
                {
                    painter.setBrush(greenBrush);
                }
                else
                {
                    painter.setBrush(redBrush);
                }
            }

            drawSquare(painter, Coordinates{x, y});
        }
    }
}
