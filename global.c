#include "headers/global.h"

/*ascii characters for the chess pieces*/
char ascii_character[] = {".-prnbqkPRNBQK "}; //ascii character for the pieces

/**representing the chess board**/
int chess_board[BOARD_SIZE][BOARD_SIZE] =
{
    {R, N, B, Q, K, B, N, R},
    {P, P, P, P, P, P, P, P},
    {j, i, j, i, j, i, j, i},
    {i, j, i, j, i, j, i, j},
    {j, i, j, i, j, i, j, i},
    {i, j, i, j, i, j, i, j},
    {p, p, p, p, p, p, p, p},
    {r, n, b, q, k, b, n, r}
};

/*tmp chess board to fill the spaces in the main board*/
int empty_board[BOARD_SIZE][BOARD_SIZE] =
{
    {j, i, j, i, j, i, j, i},
    {i, j, i, j, i, j, i, j},
    {j, i, j, i, j, i, j, i},
    {i, j, i, j, i, j, i, j},
    {j, i, j, i, j, i, j, i},
    {i, j, i, j, i, j, i, j},
    {j, i, j, i, j, i, j, i},
    {i, j, i, j, i, j, i, j}
};

int out_pieces[BOARD_SIZE][4] =
{
    {o, o, o, o},
    {o, o, o, o},
    {o, o, o, o},
    {o, o, o, o},
    {o, o, o, o},
    {o, o, o, o},
    {o, o, o, o},
    {o, o, o, o}
};


int steps = 0, undo_counter = 0; //steps is used as counter for the steps in the undo, undo counter is used to check how many undo can be redo
int turn = 1; //to turn the turns each time
int out_w = 0, out_rows_w = 0, out_b = 0, out_rows_b = 0; // variables to arrange the out pieces
int W_rank = 7, W_file = 4, B_rank = 0, B_file = 4, W_moved = 0, B_moved = 0; //kings variables
int r1 = 0, r2 = 0, r3 = 0, r4 = 0; //if the rook moved turn it to one
int w_attak_piece_rank =0,w_attak_piece_file =0;
int attak_piece_rank =0,attak_piece_file =0;
int save_2=1,save_1=1;
Move moves[100]; //array to hold the moves
