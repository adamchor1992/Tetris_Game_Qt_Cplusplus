#include "view/game_arena.h"
#include "view/gui_config.h"

#include <QPainter>

GameArena::GameArena(QWidget* parent) : QWidget(parent)
{

}

void GameArena::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    QPainter painter(this);

    if(abstractBlock_)
    {
        drawBlock(painter);
    }

    if(placedSquares_)
    {
        drawPlacedSquares(painter);
    }

    drawGameArena(painter);
}

void GameArena::drawBlock(QPainter& painter) const
{
    painter.setBrush(abstractBlock_->getColor());
    painter.setPen(Qt::NoPen);

    for(int i = 0; i < AbstractBlock::SIZE; ++i)
    {
        const Coordinates& coordinates = abstractBlock_->getSquareCoordinates(i);

        painter.drawRect((coordinates.x - 1) * GuiConfig::GameArenaParameters::BLOCK_SQUARE_SIZE + GuiConfig::GameArenaParameters::WALL_OFFSET,
                         (coordinates.y - 1) * GuiConfig::GameArenaParameters::BLOCK_SQUARE_SIZE + GuiConfig::GameArenaParameters::WALL_OFFSET,
                         GuiConfig::GameArenaParameters::BLOCK_SQUARE_SIZE,
                         GuiConfig::GameArenaParameters::BLOCK_SQUARE_SIZE);
    }
}

void GameArena::drawPlacedSquares(QPainter& painter) const
{
    for(auto& square : placedSquares_->getCoordinatesToSquaresMapping())
    {
        const QPen pen(Qt::NoPen);
        const QBrush brush(square->getColor());
        const Coordinates& coordinates = square->getCoordinates();

        painter.setPen(pen);
        painter.setBrush(brush);

        painter.drawRect((coordinates.x - 1) * GuiConfig::GameArenaParameters::BLOCK_SQUARE_SIZE + GuiConfig::GameArenaParameters::WALL_OFFSET,
                         (coordinates.y - 1) * GuiConfig::GameArenaParameters::BLOCK_SQUARE_SIZE + GuiConfig::GameArenaParameters::WALL_OFFSET,
                         GuiConfig::GameArenaParameters::BLOCK_SQUARE_SIZE,
                         GuiConfig::GameArenaParameters::BLOCK_SQUARE_SIZE);
    }
}

void GameArena::drawGameArena(QPainter& painter) const
{
    QBrush whiteBrush(GuiConfig::GameArenaParameters::WALL_COLOR);
    QPen wallPen(whiteBrush, GuiConfig::GameArenaParameters::WALL_THICKNESS);

    painter.setPen(wallPen);
    painter.setBrush(whiteBrush);

    /*Left wall*/
    painter.drawLine(GuiConfig::GameArenaParameters::LEFT_BORDER_X + GuiConfig::GameArenaParameters::LEFT_BORDER_OFFSET_X,
                     GuiConfig::GameArenaParameters::BOTTOM_Y,
                     GuiConfig::GameArenaParameters::LEFT_BORDER_X + GuiConfig::GameArenaParameters::LEFT_BORDER_OFFSET_X,
                     GuiConfig::GameArenaParameters::TOP_Y);

    /*Right wall*/
    painter.drawLine(GuiConfig::GameArenaParameters::RIGHT_BORDER_X + GuiConfig::GameArenaParameters::RIGHT_BORDER_OFFSET_X,
                     GuiConfig::GameArenaParameters::BOTTOM_Y,
                     GuiConfig::GameArenaParameters::RIGHT_BORDER_X + GuiConfig::GameArenaParameters::RIGHT_BORDER_OFFSET_X,
                     GuiConfig::GameArenaParameters::TOP_Y);

    /*Bottom wall*/
    painter.drawLine(GuiConfig::GameArenaParameters::LEFT_BORDER_X,
                     GuiConfig::GameArenaParameters::BOTTOM_Y + GuiConfig::GameArenaParameters::BOTTOM_OFFSET_Y,
                     GuiConfig::GameArenaParameters::RIGHT_BORDER_X,
                     GuiConfig::GameArenaParameters::BOTTOM_Y + GuiConfig::GameArenaParameters::BOTTOM_OFFSET_Y);

    /*Top wall*/
    painter.drawLine(GuiConfig::GameArenaParameters::LEFT_BORDER_X,
                     GuiConfig::GameArenaParameters::TOP_Y + GuiConfig::GameArenaParameters::TOP_OFFSET_Y,
                     GuiConfig::GameArenaParameters::RIGHT_BORDER_X,
                     GuiConfig::GameArenaParameters::TOP_Y + GuiConfig::GameArenaParameters::TOP_OFFSET_Y);
}

void GameArena::updateBlock(AbstractBlock* abstractBlock)
{
    abstractBlock_ = abstractBlock;
    update();
}

void GameArena::updatePlacedSquares(PlacedSquares* placedSquares)
{
    placedSquares_ = placedSquares;
    update();
}
