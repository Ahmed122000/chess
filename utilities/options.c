#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/global.h"
#include "../headers/utilities/options.h"
#include "../headers/utilities/delay.h"

/*undo function*/
void undo()
{
    //undo can't happen more than number of steps that was played
    if(steps > 0 && moves[steps - 1].out != 1)
    {
        //return the pieces for the last move
        chess_board[moves[steps-1].rank1][moves[steps-1].file1] = moves[steps - 1].piece1;
        chess_board[moves[steps-1].rank2][moves[steps-1].file2] = moves[steps - 1].piece2;
        //change turns
        if(turn == 1)
            turn = 2;
        else
            turn = 1;
        steps --; undo_counter++;

    }
    else if(steps > 0 && moves[steps - 1].out == 1)
    {
        //return the pieces for the last move and if there any piece out
        chess_board[moves[steps-1].rank1][moves[steps-1].file1] = moves[steps - 1].piece1;
        chess_board[moves[steps-1].rank2][moves[steps-1].file2] = moves[steps - 1].piece2;
        out_pieces[moves[steps - 1].rank_out][moves[steps - 1].file_out] = o;
        //change turns
        if(turn == 1)
            turn = 2;
        else
            turn = 1;
        steps --; undo_counter++;
    }

    else
    {
        printf("there is on other left moves\n");
        delay(1500);//delay some time to represent the last message
    }
}

/*redo function*/
void redo()
{   //undo can't happen more than the undo
    if(undo_counter > 0 && moves[steps].out != 1)
    {
        //re-move the pieces like before undo
        chess_board[moves[steps].rank2][moves[steps].file2] = chess_board[moves[steps].rank1][moves[steps].file1];
        chess_board[moves[steps].rank1][moves[steps].file1] = empty_board[moves[steps].rank1][moves[steps].file1];
        //change turns
        if(turn == 2)
            turn = 1;
        else
            turn = 2;

        undo_counter--; steps++;
    }
    else if(undo_counter > 0 && moves[steps].out == 1)
    {
        //re-move the piece like before undo
        out_pieces[moves[steps].rank_out][moves[steps].file_out] = chess_board[moves[steps].rank2][moves[steps].file2];
        chess_board[moves[steps].rank2][moves[steps].file2] = chess_board[moves[steps].rank1][moves[steps].file1];
        chess_board[moves[steps].rank1][moves[steps].file1] = empty_board[moves[steps].rank1][moves[steps].file1];
        //change turns
        if(turn == 2)
            turn = 1;
        else
            turn = 2;

        undo_counter--; steps++;
    }
    else
    {
        printf("REDO is not available");
        delay(1500); //delay some time to read the last message
    }
}