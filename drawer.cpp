#include "Drawer.h"

Drawer::Drawer(QGraphicsScene& scene) : m_Scene(scene)
{
    m_BlackPen = QPen(Qt::black);
    m_BlackBrush = QBrush(Qt::black);
}

void Drawer::DrawGameArena()
{
    QBrush whiteBrush(GameArenaParameters::WALL_COLOR);
    QPen wallPen(whiteBrush, GameArenaParameters::WALL_THICKNESS);

    /*Left wall*/
    m_Scene.addLine(GameArenaParameters::LEFT_BORDER_X + GameArenaParameters::LEFT_BORDER_X_OFFSET,
                    GameArenaParameters::BOTTOM_Y,
                    GameArenaParameters::LEFT_BORDER_X + GameArenaParameters::LEFT_BORDER_X_OFFSET,
                    GameArenaParameters::TOP_Y,
                    wallPen);
    /*Right wall*/
    m_Scene.addLine(GameArenaParameters::RIGHT_BORDER_X + GameArenaParameters::RIGHT_BORDER_X_OFFSET,
                    GameArenaParameters::BOTTOM_Y,
                    GameArenaParameters::RIGHT_BORDER_X + GameArenaParameters::RIGHT_BORDER_X_OFFSET,
                    GameArenaParameters::TOP_Y,
                    wallPen);
    /*Bottom wall*/
    m_Scene.addLine(GameArenaParameters::LEFT_BORDER_X,
                    GameArenaParameters::BOTTOM_Y + GameArenaParameters::BOTTOM_Y_OFFSET,
                    GameArenaParameters::RIGHT_BORDER_X,
                    GameArenaParameters::BOTTOM_Y + GameArenaParameters::BOTTOM_Y_OFFSET,
                    wallPen);
    /*Top wall*/
    m_Scene.addLine(GameArenaParameters::LEFT_BORDER_X,
                    GameArenaParameters::TOP_Y + GameArenaParameters::TOP_Y_OFFSET,
                    GameArenaParameters::RIGHT_BORDER_X,
                    GameArenaParameters::TOP_Y + GameArenaParameters::TOP_Y_OFFSET,
                    wallPen);
}

bool Drawer::CheckCoordinatesValidity(int x, int y)
{
    try
    {
        if(x < 1 || x > 10)
        {
            throw 1;
        }
        if(y < 1 || y > 20)
        {
            throw 2;
        }
    }
    catch(int exception)
    {
        switch(exception)
        {
        case 1:
            qDebug() << "Wrong x coordinate";
            return false;
        case 2:
            qDebug() << "Wrong y coordinate";
            return false;
        default:
            qDebug() << "Unknown exception in CheckCoordinatesValidity method";
            return false;
        }
    }

    return true;
}

bool Drawer::CheckCoordinatesValidity(QVector<int> blockCoordinates)
{
    if(blockCoordinates.size() != 8)
    {
        qDebug() << "Bad block coordinates, it should be 4 pairs of values";
        return false;
    }

    for(int i=0; i<4; i=i+2)
    {
        int x = blockCoordinates.at(i);
        int y = blockCoordinates.at(i+1);

        try
        {
            if(x < 1 || x > 10)
            {
                throw 1;
            }
            if(y < 1 || y > 20)
            {
                throw 2;
            }
        }
        catch(int exception)
        {
            switch(exception)
            {
            case 1:
                qDebug() << "Wrong x coordinate";
                return false;
            case 2:
                qDebug() << "Wrong y coordinate";
                return false;
            default:
                qDebug() << "Unknown exception in CheckCoordinatesValidity method";
                return false;
            }
        }
    }

    return true;
}

void Drawer::DrawSquare(int x, int y, QBrush brush)
{
    if(CheckCoordinatesValidity(x,y))
    {
        m_Scene.addRect((x-1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                        (y-1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                        GameArenaParameters::BLOCK_SQUARE_SIZE,
                        GameArenaParameters::BLOCK_SQUARE_SIZE,
                        Qt::NoPen,
                        brush);
    }
}

void Drawer::DrawPlacedBlocks(PlacedBlocks const* p_PlacedBlocks)
{
    m_Scene.clear();

    QBrush whiteBrush(Qt::white);
    QPen sideWallsPen(whiteBrush, 6);
    QPen bottomWallPen(whiteBrush, 5);

    DrawGameArena();

    for(auto item : p_PlacedBlocks->getPlacedBlocksArray().keys()) //item is key
    {
        if(p_PlacedBlocks->getPlacedBlocksArray().value(item) != nullptr)
        {
            int x = item.first;
            int y = item.second;

            DrawSquare(x, y, Qt::white);
        }
    }
}

QVector<QGraphicsRectItem*> Drawer::DrawBlock(QVector<int> blockCoordinates, QColor randomColor)
{
    QVector<QGraphicsRectItem*> squaresGraphicPointers;

    QPen randomColorPen(randomColor);
    QBrush randomColorBrush(randomColor);

    if(CheckCoordinatesValidity(blockCoordinates))
    {
        for(int i=0 ; i<8; i=i+2)
        {
            squaresGraphicPointers.append(m_Scene.addRect((blockCoordinates.at(i)-1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                                          (blockCoordinates.at(i+1)-1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                                          GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                          GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                          randomColorPen,
                                                          randomColorBrush));
        }
    }
    return squaresGraphicPointers;
}

void Drawer::DeleteBlock(QVector<QGraphicsRectItem*> blockRectGraphicPointers)
{
    for(QGraphicsRectItem *item : blockRectGraphicPointers)
    {
        m_Scene.removeItem(item);
    }
}

void Drawer::DrawAllPossibleSquares()
{
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);

    for(int column = 0; column < GameArenaParameters::MAX_BLOCK_COLUMNS; ++column)
    {
        for(int row = 0; row < GameArenaParameters::MAX_BLOCK_ROWS; ++row)
        {
            /*Different block color every second column*/
            if(column % 2 == 0)
            {
                if(row % 2 == 0) /*Different block color every second row*/
                {
                    m_Scene.addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    row * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    Qt::NoPen,
                                    blueBrush);
                }
                else
                {
                    m_Scene.addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    row * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
            else
            {
                if(row % 2 != 0)
                {
                    m_Scene.addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    row * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    Qt::NoPen,
                                    blueBrush);
                }
                else
                {
                    m_Scene.addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    row * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
        }
    }
}
