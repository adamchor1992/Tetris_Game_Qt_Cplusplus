#include "block.h"

Block::Block(QString _shape, QObject *parent) : QObject(parent)
{
    shape = _shape;
    central_square_x = 5;
    central_square_y = 1;
    int square1posx = 0;
    int square1posy = 0;
    int square2posx = 0;
    int square2posy = 0;
    int square3posx = 0;
    int square3posy = 0;

    centralsquare = new Square(central_square_x, central_square_y, this);

    if(shape == "S")
    {
        square1posx = central_square_x - 1;
        square1posy = central_square_y + 1;
        square2posx = central_square_x;
        square2posy = central_square_y + 1;
        square3posx = central_square_x + 1;
        square3posy = central_square_y;
    }
    else if(shape == "Z")
    {
        square1posx = central_square_x - 1;
        square1posy = central_square_y;
        square2posx = central_square_x;
        square2posy = central_square_y + 1;
        square3posx = central_square_x + 1;
        square3posy = central_square_y + 1;
    }
    else if(shape == "I")
    {
        square1posx = central_square_x - 1;
        square1posy = central_square_y;
        square2posx = central_square_x + 1;
        square2posy = central_square_y;
        square3posx = central_square_x + 2;
        square3posy = central_square_y;
    }
    else if(shape == "J")
    {
        square1posx = central_square_x - 1;
        square1posy = central_square_y;
        square2posx = central_square_x + 1;
        square2posy = central_square_y;
        square3posx = central_square_x + 1;
        square3posy = central_square_y + 1;
    }
    else if(shape == "L")
    {
        square1posx = central_square_x - 1;
        square1posy = central_square_y + 1;
        square2posx = central_square_x - 1;
        square2posy = central_square_y;
        square3posx = central_square_x + 1;
        square3posy = central_square_y;
    }
    else if(shape == "O")
    {
        square1posx = central_square_x;
        square1posy = central_square_y + 1;
        square2posx = central_square_x + 1;
        square2posy = central_square_y + 1;
        square3posx = central_square_x + 1;
        square3posy = central_square_y;
    }
    else if(shape == "T")
    {
        square1posx = central_square_x - 1;
        square1posy = central_square_y;
        square2posx = central_square_x;
        square2posy = central_square_y + 1;
        square3posx = central_square_x + 1;
        square3posy = central_square_y;
    }
    else
    {
        qDebug() << "UNKNOWN SHAPE, ABORTING";
        return;
    }

    square1 = new Square(square1posx, square1posy, this);
    square2 = new Square(square2posx, square2posy, this);
    square3 = new Square(square3posx, square3posy, this);

    blockSquares.append(square1);
    blockSquares.append(square2);
    blockSquares.append(square3);

    blockCoordinates.append(central_square_x);
    blockCoordinates.append(central_square_y);

    for(Square* item : blockSquares)
    {
        blockCoordinates.append(item->getX());
        blockCoordinates.append(item->getY());
    }
}

void Block::moveBlock(int direction)
{
    //direction 0 is left, 1 is right
    //block has 4 pairs of coordinates {1,1,2,2,3,3,4,4}

    if(direction == 0) // move to the left
    {
        for(int i=0; i < blockCoordinates.size(); i=i+2)
        {
            int current_x = blockCoordinates.at(i); //x coordinate
            int current_y = blockCoordinates.at(i+1); //y coordinate

            int new_x = current_x - 1; //x decreases
            int new_y = current_y; //y does not change

            blockCoordinates[i] = new_x;
            blockCoordinates[i+1] = new_y;
        }
    }
    else if(direction == 1) // move to the right
    {
        for(int i=0; i < blockCoordinates.size(); i=i+2)
        {
            int current_x = blockCoordinates.at(i); //x coordinate
            int current_y = blockCoordinates.at(i+1); //y coordinate

            int new_x = current_x + 1; //x increases
            int new_y = current_y; //y does not change

            blockCoordinates[i] = new_x;
            blockCoordinates[i+1] = new_y;
        }
    }
    else //wrong direction
    {
        qDebug() << "WRONG DIRECTION";
    }
}

void Block::rotateBlock()
{
    //first two coordinates is central square
    if(shape == "S")
    {

    }
    else if(shape == "Z")
    {

    }
    else if(shape == "I")
    {

    }
    else if(shape == "J")
    {

    }
    else if(shape == "L")
    {

    }
    else if(shape == "O")
    {
        return;
    }
    else if(shape == "T")
    {

    }
    else
    {
        qDebug() << "Rotate block error";
    }
}

bool Block::isSquaresLeftOfBlock(const PlacedBlocks *placed_blocks)
{
    for(int i=0; i<blockCoordinates.size(); i=i+2)
    {
        int current_x = blockCoordinates.at(i); //x coordinate
        int current_y = blockCoordinates.at(i+1); //y coordinate

        int left_block_x = current_x - 1; // x is decreased
        int left_block_y = current_y; // y does not change

        if(left_block_x < 1) // if there is left wall next to the block
        {
            return true;
        }

        //QPair<int,int> current_coordinates_pair(current_x,current_y);
        QPair<int,int> left_of_block_coordinates_pair(left_block_x,left_block_y);

        //check if there is some block to the left of current block
        if(placed_blocks->placedBlocksArray.value(left_of_block_coordinates_pair) != 0)
        {
            return true;
        }
    }

    return false;
}

bool Block::isSquaresRightOfBlock(const PlacedBlocks *placed_blocks)
{
    for(int i=0; i<blockCoordinates.size(); i=i+2)
    {
        int current_x = blockCoordinates.at(i); //x coordinate
        int current_y = blockCoordinates.at(i+1); //y coordinate

        int right_block_x = current_x + 1; // x is increased
        int right_block_y = current_y; // y does not change

        if(right_block_x > 10) // if there is left wall next to the block
        {
            return true;
        }

        //QPair<int,int> current_coordinates_pair(current_x,current_y);
        QPair<int,int> right_of_block_coordinates_pair(right_block_x,right_block_y);

        //check if there is some block to the right of current block
        if(placed_blocks->placedBlocksArray.value(right_of_block_coordinates_pair) != 0)
        {
            return true;
        }
    }

    return false;
}

bool Block::isSquaresUnderBlock(const PlacedBlocks *placed_blocks)
{
    //block has 4 pairs of coordinates {1,1,2,2,3,3,4,4}
    for(int i=0; i < blockCoordinates.size(); i=i+2)
    {
        int current_x = blockCoordinates.at(i); //x coordinate
        int current_y = blockCoordinates.at(i+1); //y coordinate

        int below_block_x = current_x; // x does not change
        int below_block_y = current_y + 1; // y is increased

        if(below_block_y > 20) // if there is bottom under block
        {
            return true;
        }

        //QPair<int,int> current_coordinates_pair(current_x,current_y);
        QPair<int,int> below_block_coordinates_pair(below_block_x,below_block_y);

        //check if there is some block below current block
        if(placed_blocks->placedBlocksArray.value(below_block_coordinates_pair) != 0)
        {
            return true;
        }
    }
    return false;
}

void Block::dropBlockCoordinates()
{
    for(int i=1; i<blockCoordinates.size(); i=i+2)
    {
        blockCoordinates[i]++;
    }
}

QVector<int> Block::getBlockCoordinates()
{
    return blockCoordinates;
}
