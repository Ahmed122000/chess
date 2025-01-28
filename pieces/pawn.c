#include "../headers/global.h"
#include "../headers/pieces/pawn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int validate_pawn_move(int rank_1, int file_1, int rank_2, int file_2)
{
    int x = abs(rank_1 - rank_2);
    //white pawn movement
    if(x == 1 && file_1 == file_2 && rank_1 > rank_2 && chess_board[rank_1][file_1] == p && (chess_board[rank_2][file_2] == i || chess_board[rank_2][file_2] == j))
        return 1;
    //black pawn movement
    else if(x == 1 && file_1 == file_2 && rank_1 < rank_2 && chess_board[rank_1][file_1] == P && (chess_board[rank_2][file_2] == i || chess_board[rank_2][file_2] == j))
        return 1;
    //first two steps for the pawns
    else if(x == 2 && file_1 == file_2)
    {
        if((chess_board[rank_1][file_1] == p && rank_1 == 6 && rank_1 > rank_2) || (chess_board[rank_1][file_1] == P && rank_1 == 1 && rank_1 < rank_2))
            return 1;
        else
            return 0;
    }
    //move to attack
    else if(chess_board[rank_1][file_1] == P && rank_2 == rank_1 + 1 && file_2 == file_1 + 1 && chess_board[rank_2][file_2] != i && chess_board[rank_2][file_2] != j)
        return 1;
    else if(chess_board[rank_1][file_1] == P &&rank_2 == rank_1 + 1 && file_2 == file_1 - 1 && chess_board[rank_2][file_2] != i && chess_board[rank_2][file_2] != j)
        return 1;
    else if(chess_board[rank_1][file_1] == p &&rank_2 == rank_1 - 1 && file_2 == file_1 + 1 && chess_board[rank_2][file_2] != i && chess_board[rank_2][file_2] != j)
        return 1;
    else if(chess_board[rank_1][file_1] == p &&rank_2 == rank_1 - 1 && file_2 == file_1 - 1 && chess_board[rank_2][file_2] != i && chess_board[rank_2][file_2] != j)
        return 1;
    else
        return 0;
}

void promotion(int type, int rank_2, int file_2)
{
    char pro;
    if(type == 2) //promote white pawn
    {
        printf("enter the piece you want to promote to(r, n, b, q): ");
        scanf("%c%*c", &pro);
        switch(pro)
        {
            case 'r':
                chess_board[rank_2][file_2] = r;
                break;
            case 'n':
                chess_board[rank_2][file_2] = n;
                break;
            case 'b':
                chess_board[rank_2][file_2] = b;
                break;
            case 'q':
                chess_board[rank_2][file_2] = q;
                break;
            default:
                printf("you entered invalid promotion, please enter another piece: ");
                promotion(type, rank_2, file_2);
        }
    }
    else if(type == 8)//promote black pawn
    {
        printf("enter the piece you want to promote to(R, N, B, Q): ");
        scanf("%c%*c", &pro);
        switch(pro)
        {
            case 'P':
                chess_board[rank_2][file_2] = R;
                break;
            case 'N':
                chess_board[rank_2][file_2] = N;
                break;
            case 'B':
                chess_board[rank_2][file_2] = B;
                break;
            case 'Q':
                chess_board[rank_2][file_2] = Q;
                break;
            default:
                printf("you entered invalid promotion, please enter another piece: ");
                promotion(type, rank_2, file_2);
        }
    }
}