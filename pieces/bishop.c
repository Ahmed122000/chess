#include "../headers/pieces/bishob.h"
#include "../headers/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validate_bishob_move (int rank_1, int file_1, int rank_2, int file_2)
{
    int value = 0;
    int s = abs(rank_1 - rank_2);
    int v = abs(file_1 - file_2);
    if(v == s)
    {
        if(s == 1) //move only 1 step
        {
            value = 1;
        }
        else
        {
            for (int w = 1; w < s ; w++)
            {
                if (rank_1 > rank_2 && file_1 < file_2) //move to eastern north
                {
                    if (chess_board[rank_1 - w][file_1 + w] == i || chess_board[rank_1 - w][file_1 + w] == j)
                    {
                        value = 1;
                    }
                    else
                    {
                        value=0;
                        break;
                    }
                }
                else if (rank_1 > rank_2 && file_1 > file_2) //move to western north
                {
                    if (chess_board[rank_1 - w][file_1 - w] == i || chess_board[rank_1 - w][file_1 - w] == j)
                    {
                        value = 1;
                    }
                    else
                    {
                        value=0;
                        break;
                    }
                }
                else if (rank_1 < rank_2 && file_1 < file_2) //move to eastern south
                {
                    if (chess_board[rank_1 + w][file_1 + w] == i || chess_board[rank_1 + w][file_1 + w] == i)
                    {
                        value =1;
                    }
                    else
                    {
                        value=0;
                        break;
                    }
                }
                else //move to western south
                {
                    if (chess_board[rank_1 + w][file_1 - w] == i || chess_board[rank_1 + w][file_1 - w] == j)
                    {
                        value = 1;
                    }
                    else
                    {
                        value = 0;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        value = 0;

    }
    return value ;
}