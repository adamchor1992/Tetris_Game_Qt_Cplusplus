#include "Drawer.h"

Drawer::Drawer(QGraphicsScene* pScene)
{
    m_pScene = pScene; //now this class has direct access to main window m_Scene
    m_SquareSize = 28;

    m_RedPen = QPen(Qt::red);
    m_RedBrush = QBrush(Qt::red);
    m_BlackPen = QPen(Qt::black);
    m_BlackBrush = QBrush(Qt::black);
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
    int const squareSize = 29;

    if(CheckCoordinatesValidity(x,y))
    {
        int xposition = 6 + (x-1) * squareSize;
        int yposition = (y-1) * squareSize;

        m_pScene->addRect(xposition, yposition, m_SquareSize, m_SquareSize, m_RedPen, brush);
    }
}

void Drawer::DrawPlacedBlocks(PlacedBlocks const* p_PlacedBlocks)
{
    m_pScene->clear();

    QBrush whiteBrush(Qt::white);
    QPen sideWallsPen(whiteBrush, 6);
    QPen bottomWallPen(whiteBrush, 5);

    //m_pScene->addLine(3,0,3,585,sideWallsPen);
    //m_pScene->addLine(299,0,299,585,sideWallsPen);
    //m_pScene->addLine(3,582,298,582,bottomWallPen);

    for(auto item : p_PlacedBlocks->m_PlacedBlocksArray.keys()) //item is key
    {
        if(p_PlacedBlocks->m_PlacedBlocksArray.value(item) != nullptr)
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
            int positionX = 6 + (blockCoordinates.at(i)-1) * 29;
            int positionY = (blockCoordinates.at(i+1) - 1) * 29;

            squaresGraphicPointers.append(m_pScene->addRect(positionX, positionY, m_SquareSize, m_SquareSize, randomColorPen, randomColorBrush));
        }
    }
    return squaresGraphicPointers;
}

void Drawer::DeleteBlock(QVector<int> blockCoordinates)
{
    if(CheckCoordinatesValidity(blockCoordinates))
    {
        for(int i=0 ; i<8; i=i+2)
        {
            int positionX = 6 + (blockCoordinates.at(i)-1) * 29;
            int positionY = (blockCoordinates.at(i+1) - 1) * 29;

            m_pScene->addRect(positionX, positionY, m_SquareSize, m_SquareSize, m_BlackPen, m_BlackBrush);
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
