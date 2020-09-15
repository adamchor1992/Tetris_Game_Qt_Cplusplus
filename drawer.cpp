#include "drawer.h"

QGraphicsScene* Drawer::m_pScene = nullptr;

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

QVector<QGraphicsRectItem*> Drawer::DrawBlock(QVector<QPair<int, int> > blockCoordinates, QColor randomColor)
{
    QVector<QGraphicsRectItem*> squaresGraphicPointers;

    QPen randomColorPen(randomColor);
    QBrush randomColorBrush(randomColor);

    if(ValidateCoordinates(blockCoordinates))
    {
        for(int i=0 ; i<4; i++)
        {
            squaresGraphicPointers.append(m_pScene->addRect((blockCoordinates.at(i).first - 1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                                            (blockCoordinates.at(i).second - 1) * GameArenaParameters::BLOCK_SQUARE_SIZE + GameArenaParameters::WALL_OFFSET,
                                                            GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                            GameArenaParameters::BLOCK_SQUARE_SIZE,
                                                            randomColorPen,
                                                            randomColorBrush));
        }
    }

    return squaresGraphicPointers;
}

void Drawer::EraseBlock(QVector<QGraphicsRectItem*> blockRectGraphicPointers)
{
    for(auto squareRectGraphicPointer : blockRectGraphicPointers)
    {
        m_pScene->removeItem(squareRectGraphicPointer);
    }
}

void Drawer::RemoveAllPlacedBlocks()
{
    for(auto & graphicItem : m_pScene->items())
    {
        /*Remove all squares from scene*/
        if(dynamic_cast<QGraphicsRectItem*>(graphicItem))
        {
            m_pScene->removeItem(graphicItem);
        }
    }
}

void Drawer::DrawAllPlacedBlocks(PlacedBlocks const& placedBlocks)
{
    /*Placed blocks are first removed from scene and then placed again*/
    RemoveAllPlacedBlocks();

    for(auto coordinatesPair : placedBlocks.GetPlacedBlocksMap().keys())
    {
        if(placedBlocks.GetPlacedBlocksMap().value(coordinatesPair) == PlacedBlocks::SquarePresence::SQUARE_PRESENT)
        {
            int x = coordinatesPair.first;
            int y = coordinatesPair.second;

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

bool Drawer::ValidateCoordinates(QVector<QPair<int, int> > blockCoordinates)
{
    if(blockCoordinates.size() != 4)
    {
        assert(false);
    }

    if(blockCoordinates.at(0).first < GameArenaParameters::MIN_BLOCK_COLUMNS ||
            blockCoordinates.at(1).first < GameArenaParameters::MIN_BLOCK_COLUMNS ||
            blockCoordinates.at(2).first < GameArenaParameters::MIN_BLOCK_COLUMNS ||
            blockCoordinates.at(3).first < GameArenaParameters::MIN_BLOCK_COLUMNS )
    {
        qDebug() << "Wrong X coordinate";

        return false;
    }

    if(blockCoordinates.at(0).first > GameArenaParameters::MAX_BLOCK_COLUMNS ||
            blockCoordinates.at(1).first > GameArenaParameters::MAX_BLOCK_COLUMNS ||
            blockCoordinates.at(2).first > GameArenaParameters::MAX_BLOCK_COLUMNS ||
            blockCoordinates.at(3).first > GameArenaParameters::MAX_BLOCK_COLUMNS )
    {
        qDebug() << "Wrong X coordinate";

        return false;
    }

    if(blockCoordinates.at(0).first < GameArenaParameters::MIN_BLOCK_ROWS ||
            blockCoordinates.at(1).first < GameArenaParameters::MIN_BLOCK_ROWS ||
            blockCoordinates.at(2).first < GameArenaParameters::MIN_BLOCK_ROWS ||
            blockCoordinates.at(3).first < GameArenaParameters::MIN_BLOCK_ROWS )
    {
        qDebug() << "Wrong X coordinate";

        return false;
    }

    if(blockCoordinates.at(0).second > GameArenaParameters::MAX_BLOCK_ROWS ||
            blockCoordinates.at(1).second > GameArenaParameters::MAX_BLOCK_ROWS ||
            blockCoordinates.at(2).second > GameArenaParameters::MAX_BLOCK_ROWS ||
            blockCoordinates.at(3).second > GameArenaParameters::MAX_BLOCK_ROWS )
    {
        qDebug() << "Wrong Y coordinate";

        return false;
    }

    return true;
}
