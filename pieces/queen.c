#include "../headers/global.h"
#include "../headers/pieces/queen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validate_queen_move (int rank_1,int file_1,int rank_2,int file_2)
{
    //the queen can move in any way like the bishop or the rook

    int x = abs(rank_1 - rank_2); // number of vertically steps
    int y = abs(file_1 - file_2); // number of horizontally steps
    int value = 0;
    //moving to left or right
    if(rank_1 == rank_2 && file_1 != file_2)
    {
        if(n == 1)
            value = 1;
        else
        {
            for(int z = 1; z < y; z++)
            {
                //*moving right
                if(file_1 < file_2)
                {
                    if(chess_board[rank_1][file_1 + z] == i|| chess_board[rank_1][file_1 + z] == j)
                    {
                        value = 1;
                    }
                    else
                    {
                        value = 0;
                        break;
                    }
                }
                //*moving left
                else
                {
                    if(chess_board[rank_1][file_1 - z] == i || chess_board[rank_1][file_1 - z] == j)
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
    //*move to upwards or downwards
    else if(rank_1 != rank_2 && file_1 == file_2)
    {
        if(x == 1)
            value = 1;
        else
        {
            for(int w = 1; w < x ; w++)
            {
                //move downwards
                if(rank_1 < rank_2)
                {
                    if(chess_board[rank_1 + w][file_1] == i || chess_board[rank_1 + w][file_1] == j)
                    {
                        value = 1;
                    }
                    else
                    {
                        value = 0;
                        break;
                    }
                }
                //move upwards
                else
                {
                    if(chess_board[rank_1 - w][file_1] == i || chess_board[rank_1 - w][file_1] == j)
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
    //moving in diagonal
    else if(y == x)
    {
        if(y == 1)
            value = 1;
        else
        {
            for(int a = 1; a < x; a++)
            {
                //moving to southern north
                if(rank_1 > rank_2 && file_1 > file_2)
                {
                    if(chess_board[rank_1 - a][file_1 - a] == i || chess_board[rank_1 - a][file_1 - a] == j)
                    {
                        value = 1;
                    }
                    else
                    {
                        value=0;
                        break;
                    }
                }
                //moving to eastern north
                else if(rank_1 > rank_2 && file_1 < file_2)
                {
                    if(chess_board[rank_1 - a][file_1 + a] == i || chess_board[rank_1 - a][file_1 + a] == j)
                    {
                        value = 1;
                    }
                    else
                    {
                        value = 0;
                        break;
                    }
                }
                //moving to eastern south
                else if(rank_1 < rank_2 && file_1 < file_2)
                {
                    if(chess_board[rank_1 + a][file_1 + a] == i || chess_board[rank_1 + a][file_1 + a] == j)
                    {
                        value =1;
                    }
                    else
                    {
                        value=0;
                        break;
                    }
                }
                //moving to western south
                else
                {
                    if(chess_board[rank_1 + a][file_1 - a] == i || chess_board[rank_1 + a][file_1 - a] == j)
                    {
                        value =1;
                    }
                    else
                    {
                        value=0;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        value=0;
    }
    return value ;
}