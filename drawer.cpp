#include "drawer.h"

Drawer::Drawer()
{
    m_BlackPen = QPen(Qt::black);
    m_BlackBrush = QBrush(Qt::black);
}

void Drawer::DrawGameArena()
{
    QBrush whiteBrush(GameArenaParameters::WALL_COLOR);
    QPen wallPen(whiteBrush, GameArenaParameters::WALL_THICKNESS);

    /*Left wall*/
    m_pScene->addLine(GameArenaParameters::LEFT_BORDER_X + GameArenaParameters::LEFT_BORDER_X_OFFSET,
                    GameArenaParameters::BOTTOM_Y,
                    GameArenaParameters::LEFT_BORDER_X + GameArenaParameters::LEFT_BORDER_X_OFFSET,
                    GameArenaParameters::TOP_Y,
                    wallPen);
    /*Right wall*/
    m_pScene->addLine(GameArenaParameters::RIGHT_BORDER_X + GameArenaParameters::RIGHT_BORDER_X_OFFSET,
                    GameArenaParameters::BOTTOM_Y,
                    GameArenaParameters::RIGHT_BORDER_X + GameArenaParameters::RIGHT_BORDER_X_OFFSET,
                    GameArenaParameters::TOP_Y,
                    wallPen);
    /*Bottom wall*/
    m_pScene->addLine(GameArenaParameters::LEFT_BORDER_X,
                    GameArenaParameters::BOTTOM_Y + GameArenaParameters::BOTTOM_Y_OFFSET,
                    GameArenaParameters::RIGHT_BORDER_X,
                    GameArenaParameters::BOTTOM_Y + GameArenaParameters::BOTTOM_Y_OFFSET,
                    wallPen);
    /*Top wall*/
    m_pScene->addLine(GameArenaParameters::LEFT_BORDER_X,
                    GameArenaParameters::TOP_Y + GameArenaParameters::TOP_Y_OFFSET,
                    GameArenaParameters::RIGHT_BORDER_X,
                    GameArenaParameters::TOP_Y + GameArenaParameters::TOP_Y_OFFSET,
                    wallPen);
}

void Drawer::DrawSquare(int x, int y, QBrush brush)
{
    if(ValidateCoordinates(x,y))
    {
        m_pScene->addRect((x-1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                        (y-1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                        GameArenaParameters::BLOCK_SQUARE_SIZE,
                        GameArenaParameters::BLOCK_SQUARE_SIZE,
                        Qt::NoPen,
                        brush);
    }
}

QVector<QGraphicsRectItem*> Drawer::DrawBlock(QVector<int> blockCoordinates, QColor randomColor)
{
    QVector<QGraphicsRectItem*> squaresGraphicPointers;

    QPen randomColorPen(randomColor);
    QBrush randomColorBrush(randomColor);

    if(ValidateCoordinates(blockCoordinates))
    {
        for(int i=0 ; i<8; i=i+2)
        {
            squaresGraphicPointers.append(m_pScene->addRect((blockCoordinates.at(i)-1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                                          (blockCoordinates.at(i+1)-1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                                          GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                          GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                          randomColorPen,
                                                          randomColorBrush));
        }
    }

    return squaresGraphicPointers;
}

void Drawer::DeletePlacedSquare(int x, int y, PlacedBlocks const* p_PlacedBlocks)
{
    if(ValidateCoordinates(x,y))
    {
        QPair<int, int> coordinatesPair;

        if(p_PlacedBlocks->GetPlacedBlocksMap().value(coordinatesPair) != nullptr)
        {
            m_pScene->removeItem(p_PlacedBlocks->GetPlacedBlocksMap().value(coordinatesPair));
        }
        else
        {
            assert(false);
        }
    }
}

void Drawer::DeleteBlock(QVector<QGraphicsRectItem*> blockRectGraphicPointers)
{
    for(QGraphicsRectItem *item : blockRectGraphicPointers)
    {
        m_pScene->removeItem(item);
    }
}

void Drawer::DrawAllPlacedBlocks(PlacedBlocks const& p_PlacedBlocks)
{
    m_pScene->clear();

    DrawGameArena();

    for(auto item : p_PlacedBlocks.GetPlacedBlocksMap().keys()) //item is key
    {
        if(p_PlacedBlocks.GetPlacedBlocksMap().value(item) != nullptr)
        {
            int x = item.first;
            int y = item.second;

            DrawSquare(x, y, Qt::white);
        }
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
                    m_pScene->addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    row * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    Qt::NoPen,
                                    blueBrush);
                }
                else
                {
                    m_pScene->addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
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
                    m_pScene->addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    row * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    GameArenaParameters::BLOCK_SQUARE_SIZE,
                                    Qt::NoPen,
                                    blueBrush);
                }
                else
                {
                    m_pScene->addRect(column * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
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

bool Drawer::ValidateCoordinates(int x, int y)
{
    if(x < 1 || x > GameArenaParameters::MAX_BLOCK_COLUMNS)
    {
        qDebug("Wrong X coordinate");

        return false;
    }

    if(y < 1 || y > GameArenaParameters::MAX_BLOCK_ROWS)
    {
        qDebug("Wrong Y coordinate");

        return false;
    }

    return true;
}

bool Drawer::ValidateCoordinates(QVector<int> blockCoordinates)
{
    if(blockCoordinates.size() != 8)
    {
        assert(false);
    }

    /*Even coordinates are columns*/
    if(blockCoordinates.at(0) > GameArenaParameters::MAX_BLOCK_COLUMNS ||
            blockCoordinates.at(2) > GameArenaParameters::MAX_BLOCK_COLUMNS ||
            blockCoordinates.at(4) > GameArenaParameters::MAX_BLOCK_COLUMNS ||
            blockCoordinates.at(6) > GameArenaParameters::MAX_BLOCK_COLUMNS )
    {
        qDebug() << "Wrong X coordinate";

        assert(false);
    }

    /*Odd coordinates are rows*/
    if(blockCoordinates.at(1) > GameArenaParameters::MAX_BLOCK_ROWS ||
            blockCoordinates.at(3) > GameArenaParameters::MAX_BLOCK_ROWS ||
            blockCoordinates.at(5) > GameArenaParameters::MAX_BLOCK_ROWS ||
            blockCoordinates.at(7) > GameArenaParameters::MAX_BLOCK_ROWS )
    {
        qDebug() << "Wrong Y coordinate";

        assert(false);
    }

    return true;
}
