#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/pieces/rook.h"
#include "../headers/global.h"

int validate_rook_move (int rank_1, int file_1, int rank_2, int file_2)
{
    int valid;
    if (rank_1 == rank_2 && file_1 != file_2)
    {
        int n = abs(file_2 - file_1);
        //check for one step
        if(n == 1)
        {
            valid = 1;
        }
        /*check that there is nothing to prevent the move*/
        else
        {
            for (int z = 1; z < n; z++)
            {
                //*moving right
                if (file_1 < file_2)
                {
                    if (chess_board[rank_1][file_1 + z] != i && chess_board[rank_1][file_1 + z] != j)
                    {
                        valid = 0;
                        break;
                    }
                    else
                    {
                        valid = 1;
                    }

                }
                //*moving left
                else
                {
                    if (chess_board[rank_1][file_1 - z] != i && chess_board[rank_1][file_1 - z] != j)
                    {
                        valid = 0;
                        break;
                    }
                    else
                    {
                        valid = 1;
                    }

                }
            }
        }
    }
        //*move in ranks
        else if (rank_1 != rank_2 && file_1 == file_2)
        {
            int m = abs(rank_1 - rank_2);
            if(m == 1)
                valid = 1;
            else
            {
                for (int w = 1; w < m; w++)
                {
                    //move upwards
                    if (rank_1 > rank_2)
                    {
                        if (chess_board[rank_1 - w][file_1] != i && chess_board[rank_1 - w][file_1] != j)
                        {
                            valid = 0;
                            break;
                        }
                        else
                        {
                            valid = 1;
                        }
                    }
                    //move downwards
                    else
                    {
                        if (chess_board[rank_1 + w][file_1] != i && chess_board[rank_1 + w][file_1] != j)
                        {
                            valid = 0;
                            break;
                        }
                        else
                        {
                            valid = 1;
                        }

                    }

                }
            }
        }
    else
    {
        valid = 0;
    }
    return valid;
}