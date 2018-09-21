#include "lblock.h"

LBlock::LBlock() : Block(QString("L"))
{
    current_rotation = 0;
}

void LBlock::rotateBlock()
{
    central_square_x = blockCoordinates.at(2);
    central_square_y = blockCoordinates.at(3);

    if(current_rotation == 0)
    {
        int new_square1_x = central_square_x - 1;
        int new_square1_y = central_square_y;
        int new_central_square_x = central_square_x;
        int new_central_square_y = central_square_y;
        int new_square2_x = central_square_x;
        int new_square2_y = central_square_y + 1;
        int new_square3_x = central_square_x;
        int new_square3_y = central_square_y + 2;

        if(new_square1_x > 10 || new_square1_x < 1)
        {
            return;
        }
        if(new_central_square_x > 10 || new_central_square_x < 1)
        {
            return;
        }
        if(new_square2_x > 10 || new_square2_x < 1)
        {
            return;
        }
        if(new_square3_x > 10 || new_square3_x < 1)
        {
            return;
        }

        if(new_square1_y > 20 || new_square1_y < 1)
        {
            return;
        }
        if(new_central_square_y > 20 || new_central_square_y < 1)
        {
            return;
        }
        if(new_square2_y > 20 || new_square2_y < 1)
        {
            return;
        }
        if(new_square3_y > 20 || new_square3_y < 1)
        {
            return;
        }

        blockCoordinates[0] = new_square1_x;
        blockCoordinates[1] = new_square1_y;
        blockCoordinates[2] = new_central_square_x;
        blockCoordinates[3] = new_central_square_y;
        blockCoordinates[4] = new_square2_x;
        blockCoordinates[5] = new_square2_y;
        blockCoordinates[6] = new_square3_x;
        blockCoordinates[7] = new_square3_y;

        current_rotation = 1;
    }
    else if(current_rotation == 1)
    {
        int new_square1_x = central_square_x;
        int new_square1_y = central_square_y - 1;
        int new_central_square_x = central_square_x;
        int new_central_square_y = central_square_y;
        int new_square2_x = central_square_x - 1;
        int new_square2_y = central_square_y;
        int new_square3_x = central_square_x - 2;
        int new_square3_y = central_square_y;

        if(new_square1_x > 10 || new_square1_x < 1)
        {
            return;
        }
        if(new_central_square_x > 10 || new_central_square_x < 1)
        {
            return;
        }
        if(new_square2_x > 10 || new_square2_x < 1)
        {
            return;
        }
        if(new_square3_x > 10 || new_square3_x < 1)
        {
            return;
        }

        if(new_square1_y > 20 || new_square1_y < 1)
        {
            return;
        }
        if(new_central_square_y > 20 || new_central_square_y < 1)
        {
            return;
        }
        if(new_square2_y > 20 || new_square2_y < 1)
        {
            return;
        }
        if(new_square3_y > 20 || new_square3_y < 1)
        {
            return;
        }

        blockCoordinates[0] = new_square1_x;
        blockCoordinates[1] = new_square1_y;
        blockCoordinates[2] = new_central_square_x;
        blockCoordinates[3] = new_central_square_y;
        blockCoordinates[4] = new_square2_x;
        blockCoordinates[5] = new_square2_y;
        blockCoordinates[6] = new_square3_x;
        blockCoordinates[7] = new_square3_y;

        current_rotation = 2;
    }
    else if(current_rotation == 2)
    {
        int new_square1_x = central_square_x + 1;
        int new_square1_y = central_square_y;
        int new_central_square_x = central_square_x;
        int new_central_square_y = central_square_y;
        int new_square2_x = central_square_x;
        int new_square2_y = central_square_y - 1;
        int new_square3_x = central_square_x;
        int new_square3_y = central_square_y - 2;

        if(new_square1_x > 10 || new_square1_x < 1)
        {
            return;
        }
        if(new_central_square_x > 10 || new_central_square_x < 1)
        {
            return;
        }
        if(new_square2_x > 10 || new_square2_x < 1)
        {
            return;
        }
        if(new_square3_x > 10 || new_square3_x < 1)
        {
            return;
        }

        if(new_square1_y > 20 || new_square1_y < 1)
        {
            return;
        }
        if(new_central_square_y > 20 || new_central_square_y < 1)
        {
            return;
        }
        if(new_square2_y > 20 || new_square2_y < 1)
        {
            return;
        }
        if(new_square3_y > 20 || new_square3_y < 1)
        {
            return;
        }

        blockCoordinates[0] = new_square1_x;
        blockCoordinates[1] = new_square1_y;
        blockCoordinates[2] = new_central_square_x;
        blockCoordinates[3] = new_central_square_y;
        blockCoordinates[4] = new_square2_x;
        blockCoordinates[5] = new_square2_y;
        blockCoordinates[6] = new_square3_x;
        blockCoordinates[7] = new_square3_y;

        current_rotation = 3;
    }
    else if(current_rotation == 3)
    {
        int new_square1_x = central_square_x;
        int new_square1_y = central_square_y + 1;
        int new_central_square_x = central_square_x;
        int new_central_square_y = central_square_y;
        int new_square2_x = central_square_x + 1;
        int new_square2_y = central_square_y;
        int new_square3_x = central_square_x + 2;
        int new_square3_y = central_square_y;

        if(new_square1_x > 10 || new_square1_x < 1)
        {
            return;
        }
        if(new_central_square_x > 10 || new_central_square_x < 1)
        {
            return;
        }
        if(new_square2_x > 10 || new_square2_x < 1)
        {
            return;
        }
        if(new_square3_x > 10 || new_square3_x < 1)
        {
            return;
        }

        if(new_square1_y > 20 || new_square1_y < 1)
        {
            return;
        }
        if(new_central_square_y > 20 || new_central_square_y < 1)
        {
            return;
        }
        if(new_square2_y > 20 || new_square2_y < 1)
        {
            return;
        }
        if(new_square3_y > 20 || new_square3_y < 1)
        {
            return;
        }

        blockCoordinates[0] = new_square1_x;
        blockCoordinates[1] = new_square1_y;
        blockCoordinates[2] = new_central_square_x;
        blockCoordinates[3] = new_central_square_y;
        blockCoordinates[4] = new_square2_x;
        blockCoordinates[5] = new_square2_y;
        blockCoordinates[6] = new_square3_x;
        blockCoordinates[7] = new_square3_y;

        current_rotation = 0;
    }
}
