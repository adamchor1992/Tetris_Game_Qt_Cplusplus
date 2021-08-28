#include "utilities.h"
#include <QDebug>

bool utilities::ValidateCoordinates(int x, int y)
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

bool utilities::ValidateCoordinates(const QVector<QPair<int, int> >& blockCoordinates)
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
