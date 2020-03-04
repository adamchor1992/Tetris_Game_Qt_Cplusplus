#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QVector>
#include <QColor>
#include <placed_blocks.h>

class Drawer
{
public:
    Drawer() = delete;
    Drawer(const Drawer&) = delete;
    Drawer& operator=(Drawer&) = delete;
    Drawer(const Drawer&&) = delete;
    Drawer& operator=(Drawer&&) = delete;

    static void SetScene(QGraphicsScene* pScene) {m_pScene = pScene;}
    static void DrawGameArena();
    static QVector<QGraphicsRectItem*> DrawBlock(QVector<QPair<int, int> > blockCoordinates, QColor randomColor);
    static void DrawAllPlacedBlocks(PlacedBlocks const& placedBlocks);
    static void RemoveAllPlacedBlocks(PlacedBlocks const& placedBlocks);
    static void ErasePlacedSquare(int x, int y, PlacedBlocks const& placedBlocks);
    static void EraseBlock(QVector<QGraphicsRectItem*> blockRectGraphicPointers);
    static bool ValidateCoordinates(int x, int y);
    static bool ValidateCoordinates(QVector<QPair<int, int> > blockCoordinates);

    struct GameArenaParameters
    {
        static int const WALL_THICKNESS = 5;
        static Qt::GlobalColor const WALL_COLOR = Qt::white;
        static int const WALL_OFFSET = 5;
        static int const LEFT_BORDER_X = 0;
        static int const LEFT_BORDER_X_OFFSET = +2;
        static int const RIGHT_BORDER_X = 305;
        static int const RIGHT_BORDER_X_OFFSET = +2;
        static int const BOTTOM_Y = 610;
        static int const BOTTOM_Y_OFFSET = -3;
        static int const TOP_Y = 0;
        static int const TOP_Y_OFFSET = +2;
        static int const MAX_BLOCK_ROWS = 20;
        static int const MAX_BLOCK_COLUMNS = 10;
        static int const MIN_BLOCK_ROWS = 1;
        static int const MIN_BLOCK_COLUMNS = 1;
        static int const BLOCK_SQUARE_SIZE = 30;
    };

private:
    static QGraphicsScene* m_pScene;

    static void DrawSquare(int x, int y, QBrush brush);
    static void DrawAllPossibleSquares();
};
