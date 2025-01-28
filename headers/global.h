
#ifndef GLOBAL_H
#define GLOBAL_H


#define BOARD_SIZE 8
#define MAX_MOVES 100

/*structure to hold the numeric values to use them*/
typedef struct
{
    int rank1; //represent the current row
    int file1; //represent the current column
    int piece1;
    int rank2; //represent the next row
    int file2; //represent the next column
    int piece2;
    int rank_out; //represent the row after the piece got out
    int file_out; //represent the column after the piece got out
    int out; //represent the current column
}Move;

/**representing the pieces by numeric values**/
enum {i,j,p,r,n,b,q,k,P,R,N,B,Q,K,o}; //i for white squares j for black squares and others for the pieces

/*ascii characters for the chess pieces*/
extern char ascii_character[]; //ascii character for the pieces

/**representing the chess board**/
extern int chess_board[BOARD_SIZE][BOARD_SIZE]; 

/*tmp chess board to fill the spaces in the main board*/
extern int empty_board[BOARD_SIZE][BOARD_SIZE];

extern int out_pieces[BOARD_SIZE][4];


extern int steps, undo_counter; //steps is used as counter for the steps in the undo, undo counter is used to check how many undo can be redo
extern int turn; //to turn the turns each time
extern int out_w, out_rows_w, out_b, out_rows_b; // variables to arrange the out pieces
extern int W_rank, W_file, B_rank, B_file, W_moved, B_moved; //kings variables
extern int r1, r2, r3, r4; //if the rook moved turn it to one
extern int w_attak_piece_rank, w_attak_piece_file;
extern int attak_piece_rank, attak_piece_file;
extern int save_2, save_1;
extern Move moves[100]; //array to hold the moves

#endif