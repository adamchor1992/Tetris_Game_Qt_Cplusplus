#include "drawer.h"

Drawer::Drawer(QGraphicsScene *_scene, QObject *parent) : QObject(parent)
{
    scene = _scene; //now this class has direct access to main window scene
    square_size = 28;

    red_pen = QPen(Qt::red);
    red_brush = QBrush(Qt::red);
    black_pen = QPen(Qt::black);
    black_brush = QBrush(Qt::black);
}

bool Drawer::checkCoordinatesValidity(int x, int y)
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
            qDebug() << "Unknown exception in checkCoordinatesValidity method";
            return false;
        }
    }

    return true;
}

bool Drawer::checkCoordinatesValidity(QVector<int> block_coordinates)
{
    if(block_coordinates.size() != 8)
    {
        qDebug() << "Bad block coordinates, it should be 4 pairs of values";
        return false;
    }

    for(int i=0; i<4; i=i+2)
    {
        int x = block_coordinates.at(i);
        int y = block_coordinates.at(i+1);

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
                qDebug() << "Unknown exception in checkCoordinatesValidity method";
                return false;
            }
        }
    }

    return true;
}

void Drawer::paintSquare(int x, int y)
{
    if(checkCoordinatesValidity(x,y))
    {
        int xposition = 6 + (x-1) * 29;
        int yposition = (y-1) * 29;

        scene->addRect(xposition, yposition, square_size, square_size, red_pen, red_brush);
    }
}

void Drawer::paintPlacedBlocks(const PlacedBlocks *placedblocks)
{
    scene->clear();

    QBrush white_brush(Qt::white);
    QPen side_walls_pen(white_brush, 6);
    QPen bottom_wall_pen(white_brush, 5);

    scene->addLine(3,0,3,585,side_walls_pen);
    scene->addLine(299,0,299,585,side_walls_pen);
    scene->addLine(3,582,298,582,bottom_wall_pen);

    for(auto item : placedblocks->placedBlocksArray.keys())
    {
        if(placedblocks->placedBlocksArray.value(item) != 0)
        {
            int x = item.first;
            int y = item.second;

            paintSquare(x,y);
        }
    }
}

QVector<QGraphicsRectItem*> Drawer::paintBlock(QVector<int> block_coordinates)
{
    QVector<QGraphicsRectItem*> squares_graphic_pointers;

    if(checkCoordinatesValidity(block_coordinates))
    {
        for(int i=0 ; i<8; i=i+2)
        {
            int xposition = 6 + (block_coordinates.at(i)-1) * 29;
            int yposition = (block_coordinates.at(i+1) - 1) * 29;

            squares_graphic_pointers.append(scene->addRect(xposition, yposition, square_size, square_size, red_pen, red_brush));
        }
    }
    return squares_graphic_pointers;
}

void Drawer::deleteBlock(QVector<int> block_coordinates)
{
    if(checkCoordinatesValidity(block_coordinates))
    {
        for(int i=0 ; i<8; i=i+2)
        {
            int xposition = 6 + (block_coordinates.at(i)-1) * 29;
            int yposition = (block_coordinates.at(i+1) - 1) * 29;

            scene->addRect(xposition, yposition, square_size, square_size, black_pen, black_brush);
        }
    }
}

void Drawer::deleteBlock(QVector<QGraphicsRectItem*> block_rect_graphic_pointers)
{
    for(QGraphicsRectItem *item : block_rect_graphic_pointers)
    {
        //qDebug() << item;
        scene->removeItem(item);
    }
}

void Drawer::deleteRow(QVector<int> rowsToDelete)
{
    //scene->removeItem(1);
}

