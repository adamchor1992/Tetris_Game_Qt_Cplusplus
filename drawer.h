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

    static void EraseBlock(QVector<QGraphicsRectItem*> blockRectGraphicPointers);
    static bool ValidateCoordinates(int x, int y);
    static bool ValidateCoordinates(QVector<QPair<int, int> > blockCoordinates);

    struct GameArenaParameters
    {
        static const int WALL_THICKNESS = 5;
        static Qt::GlobalColor const WALL_COLOR = Qt::white;
        static const int WALL_OFFSET = 5;
        static const int LEFT_BORDER_X = 0;
        static const int LEFT_BORDER_X_OFFSET = +2;
        static const int RIGHT_BORDER_X = 305;
        static const int RIGHT_BORDER_X_OFFSET = +2;
        static const int BOTTOM_Y = 610;
        static const int BOTTOM_Y_OFFSET = -3;
        static const int TOP_Y = 0;
        static const int TOP_Y_OFFSET = +2;
        static const int MAX_BLOCK_ROWS = 20;
        static const int MAX_BLOCK_COLUMNS = 10;
        static const int MIN_BLOCK_ROWS = 1;
        static const int MIN_BLOCK_COLUMNS = 1;
        static const int BLOCK_SQUARE_SIZE = 30;
    };

private:
    static QGraphicsScene* m_pScene;

    static void DrawSquare(int x, int y, QBrush brush);
    static void DrawAllPossibleSquares();
    static void RemoveAllPlacedBlocks();
};
