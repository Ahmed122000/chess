#include "../headers/global.h"
#include "../headers/pieces/knight.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validate_knight_move(int rank_1, int file_1, int rank_2, int file_2 )
{
    //the knight move in shape of L 2 steps then 1
    int num = 0;

    if (rank_1 == rank_2 + 2)
    {
        if (file_1 == file_2 + 1)
            num = 1;
        else if (file_1 == file_2 - 1)
            num = 1;
        else
            num = 0;
    }
    else if (rank_1 == rank_2 - 2)
    {
         if (file_1 == file_2 + 1)
            num = 1;
        else if (file_1 == file_2 - 1)
            num = 1;
        else
            num = 0;
    }
    else if (file_1 == file_2 + 2)
    {
        if (rank_1 == rank_2 + 1)
            num = 1;
        else if (rank_1 == rank_2 - 1)
            num = 1;
        else
            num = 0;
    }
    else if (file_1 == file_2 - 2)
    {
         if (rank_1 == rank_2 + 1)
            num = 1;
        else if (rank_1 == rank_2 - 1)
            num = 1;
        else
            num = 0;
    }
    else
        num = 0;

    return num ;
}