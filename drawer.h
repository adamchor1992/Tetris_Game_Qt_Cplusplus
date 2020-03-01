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
    explicit Drawer();
    void SetScene(QGraphicsScene* pScene) {m_pScene = pScene;}
    void DrawGameArena();
    QVector<QGraphicsRectItem*> DrawBlock(QVector<int> blockCoordinates, QColor randomColor);
    void DrawAllPlacedBlocks(PlacedBlocks const& p_PlacedBlocks);
    void RemoveAllPlacedBlocks(PlacedBlocks const& p_PlacedBlocks);
    void DeleteBlock(QVector<QGraphicsRectItem*> blockRectGraphicPointers);

private:
    QGraphicsScene* m_pScene;
    QPen m_RedPen;
    QBrush m_RedBrush;
    QPen m_BlackPen;
    QBrush m_BlackBrush;

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
        static int const BLOCK_SQUARE_SIZE = 30;
    };

    void DrawSquare(int x, int y, QBrush brush);
    void DeletePlacedSquare(int x, int y, PlacedBlocks const* p_PlacedBlocks);
    void DrawAllPossibleSquares();
    bool ValidateCoordinates(int x, int y);
    bool ValidateCoordinates(QVector<int> blockCoordinates);
};
