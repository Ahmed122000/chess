#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/setting.h"
#include "headers/options.h"

void print_chess_board();
void move_piece(char *position);
int rook (int rank_1, int file_1, int rank_2, int file_2);
int knight(int rank_1,int file_1,int rank_2,int file_2 );
int bishop (int rank_1, int file_1, int rank_2, int file_2);
int Queen (int rank_1,int file_1,int rank_2,int file_2);
int king(int rank_1, int file_1, int rank_2, int file_2);
int pawn(int rank_1, int file_1, int rank_2, int file_2);
void promotion(int type, int rank_2, int file_2);
int check_draw();
int check_white (int w_k_rank ,int w_k_file);
int check_BLACK (int B_k_rank ,int B_k_file);
int chek_mate_w();
int chek_mate_b();
//void save();
//void load();
//void undo();
//void redo();
void delay(int d);
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
}square;

/**representing the pieces by numeric values**/
enum {i,j,p,r,n,b,q,k,P,R,N,B,Q,K,o}; //i for white squares j for black squares and others for the pieces

/*ascii characters for the chess pieces*/
char ascii_character[] = {".-prnbqkPRNBQK "}; //ascii character for the pieces

/**representing the chess board**/
int chess_board[8][8] =
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
int tmp_chess[8][8] =
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

int out_pieces[8][4] =
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
square moves[100]; //array to hold the moves
/*********************************************************main function***************************************************/
int main()
{
    while(save_2 == 1 && save_1 == 1)
    {
        print_chess_board(); //print the board
        //check if there was any check
        if (turn == 1)
        {
            if (check_white(W_rank,W_file) == 0)
            {
                printf ("check: you have to protect your king, player 1\n\n");
            }
            printf("player one's turn:");
        }
        else if (turn == 2)
        {
            if(check_BLACK(B_rank, B_file) == 0)
            {
                printf ("check:you have to protect your king, player 2\n\n");
            }
            printf("player two's turn:");
        }
        ////draw part
        int draw = check_draw();
        if(draw == 1)
        {
            printf("DRAW\n GameOver\n");
            break;
        }
        char position[5];
        fgets(position, 6, stdin);
        // to save the game
        if(position[0] == 's' || position[0] == 'S')
        {
            char e;
            save(chess_board, out_pieces, turn, 
                out_rows_w, out_w, out_rows_b, out_b, W_moved, B_moved,
                r1, r2, r3, r4); //save the game
            printf("do you want to exit(y/n): ");
            scanf("%c%*c", &e);
            if(e == 'y' || e == 'Y')
                break;
            else if(e == 'n' || e == 'N')
                continue;
            else
            {
                printf("invalid choice\n");
                continue;
            }
        }
        else if ((position[0] == 'D' && position[1] == 'R' && position[2] == 'A' && position[3] == 'W') || (position[0] == 'd' && position[1]== 'r' && position[2] == 'a' && position[3] == 'w'))
        {
            char e,a;
            printf("do you want to draw (y/n): ");
            scanf("%c%*c", &e);
            if(e == 'y' || e == 'Y')
            {
                printf ("the other player want to draw : what about you(y/n) ?");
                scanf("%c%*c", &a);
                if(e == 'y' || e == 'Y')
                {
                    printf("Draw !!");
                    break ;
                }
                else
                    continue ;
            }
            else if(e == 'n' || e == 'N')
                continue;
            else
            {
                printf("invalid choice\n");
                continue;
            }
        }
        //to resign early
        else if ((position[0] == 'r' && position[1] == 'e') || (position[0] == 'R' && position[1] == 'E'))
        {
            if (turn == 1)
            {
                char e;
                printf("do you want to resign (y/n): ");
                scanf("%c%*c", &e);
                if(e == 'y' || e == 'Y')
                {
                    printf("black player won ");
                    break;
                }
                else if(e == 'n' || e == 'N')
                    continue;
                else
                {
                    printf("invalid choice\n");
                    continue;
                }
            }
            else if (turn == 2)
            {
                char e;
                printf("do you want to resign (y/n): ");
                scanf("%c%*c", &e);
                if(e == 'y' || e == 'Y')
                {
                    printf("white  player won ");
                    break;
                }
                else if(e == 'n' || e == 'N')
                    continue;
                else
                {
                    printf("invalid choice\n");
                    continue;
                }
            }
        }
        // to load the game
        else if(position[0] == 'l' || position[0] == 'L')
        {
            load(chess_board, out_pieces, turn, 
                out_rows_w, out_w, out_rows_b, out_b, W_moved, B_moved,
                r1, r2, r3, r4); //load the game
        }
        //undo and redo
        else if(position[0] == 'u' || position[0] == 'U')
        {
            undo(); //undo the last move
        }
        else if(position[0] == 'r' || position[0] == 'R')
        {
            redo(); //redo the game
        }
                //check that the user entered a valid input
        else
        {
            while(position[0] < 'A' || position[0] > 'H' || position[1] < '1' || position[1] > '8' || position[2] < 'A' || position[2] > 'H' || position[3] < '1' || position[3] > '8')
            {
                printf("Invalid position please enter another position: ");
                gets(position);
            }
            move_piece(position); //start moving the chosen piece
            turn = turn % 2 + 1; //turn the turns
        }
        save(chess_board, out_pieces, turn, 
                out_rows_w, out_w, out_rows_b, out_b, W_moved, B_moved,
                r1, r2, r3, r4);;
        switch(turn)
        {
            case (1):
            {
                if(save_1 == 0)
                    printf("Black player won ");
                break;
            }
            case(2):
            {
                if(save_2 == 0)
                    printf ("White player won");
                break;
            }
        }
    }
return 0;
}


/***************************************used function in the program**************************************************************/
/*print the chess board*/
void print_chess_board()
{
    system("clear"); //to clear the screen after each output
    printf("   A B C D E F G H\t  out pieces\n\n"); //names of the columns on the top
    for(int rank = 0, j = 8; rank < 8; rank++, j--)
    {
        printf("%d  ", j); //number of the row
        for(int file = 0; file < 8; file++)
        {
            printf("%c ", ascii_character[chess_board[rank][file]]);
        }
        printf(" %d", j); //number of the rows on the lee
        printf("     ");
        for(int n = 0; n < 4; n++)
        {
            printf("%c ", ascii_character[out_pieces[rank][n]]);
        }
        printf("\n");
    }
    printf("\n   A B C D E F G H"); //name of the column on the bottom
    printf("\n\n\n");
}

/*the controlling function */
void move_piece(char *position)
{
    undo_counter = 0;
    int rank_1, rank_2, file_1, file_2, valid;
        rank_1 = 8- (position[1] - 49) - 1; //find the current row for the piece
        rank_2 = 8- (position[3] - 49) - 1; //find the next row for the piece
        file_1 = position[0] - 65; // find the current column for the piece
        file_2 = position[2] - 65; // find the next column for the piece
    //check that the user don't choose an empty square
    if(chess_board[rank_1][file_1] == i || chess_board[rank_1][file_1] == j)
    {
        printf("the square is empty, please enter another square: ");
        gets(position);
        move_piece(position);
    }

    char piece = ascii_character[chess_board[rank_1][file_1]];
    switch(turn)
    {
        case 1:
            if(chess_board[rank_1][file_1] >= 2 && chess_board[rank_1][file_1] <= 7 && (chess_board[rank_2][file_2] > 7 || chess_board[rank_2][file_2] < 2))
            {
                switch(piece)
                {
                    case 'r':
                        valid = rook(rank_1, file_1, rank_2, file_2);
                        if(valid == 1 && rank_1 == 7 && file_1 == 0)
                            r1 = 1;
                        else if(valid == 1 && rank_1 == 7 && file_1 == 7)
                            r2 = 1;
                        break;
                    case 'n':
                        valid = knight(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'b':
                        valid = bishop(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'q':
                        valid = Queen(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'k':
                        valid = king(rank_1, file_1, rank_2, file_2);
                        if (valid == 1) //if the king moved save this move
                            {
                                W_rank = rank_2;
                                W_file = file_2;
                                W_moved = 1;
                            }
                        break;
                    case 'p':
                        valid = pawn(rank_1, file_1, rank_2, file_2);
                        break;
                    default:
                        printf("you choose invalid piece\n");

                }
                if(valid)
                {
                    //making history for the moves and which piece moved
                    moves[steps].rank1 = rank_1;
                    moves[steps].file1 = file_1;
                    moves[steps].piece1 = chess_board[rank_1][file_1];
                    moves[steps].rank2 = rank_2;
                    moves[steps].file2 = file_2;
                    moves[steps].piece2 = chess_board[rank_2][file_2];

                    //taking out the dead pieces
                    if(chess_board[rank_2][file_2] != i && chess_board[rank_2][file_2] != j)
                    {
                         moves[steps].out = 1;
                        if(out_b == 4) //to move between rows
                        {
                            out_rows_b ++;
                        }
                        if(out_b > 3)
                            out_b %= 4; //the row can take only 4 pieces
                        out_pieces[out_rows_b][out_b] = chess_board[rank_2][file_2]; //move it next to the board
                        out_b++;//counting the out black pieces

                    }
                    //move the piece
                    chess_board[rank_2][file_2] = chess_board[rank_1][file_1];
                    chess_board[rank_1][file_1] = tmp_chess[rank_1][file_1];
                    //in case there was any promotion
                    if((chess_board[rank_2][file_2] == p && rank_2 == 0) ||(chess_board[rank_2][file_2] == P && rank_2 == 7))
                    {
                        print_chess_board();
                        promotion(chess_board[rank_2][file_2], rank_2, file_2);
                    }
                    steps++;
                    //prevent any move that don't protect the king in case check
                    if(check_white(W_rank, W_file) == 0)
                    {
                        printf("you should protect your king\n");
                        delay(1500);
                        undo();
                    }
                }
                else
                {
                    printf("Invalid move, please enter another valid move: ");
                    gets(position);
                    move_piece(position);
                }
            }
            else
            {
                printf("Invalid move, please enter another valid move: ");
                gets(position);
                move_piece(position);
            }
            //look for checkmate
            chek_mate_b ();
            save_2 = chek_mate_b();
            break;
        case 2:
            if(chess_board[rank_1][file_1] >= 8 && chess_board[rank_1][file_1] <= 13 && (chess_board[rank_2][file_2] > 13 || chess_board[rank_2][file_2] < 8))
            {
                switch(piece)
                {
                    case 'R':
                        valid = rook(rank_1, file_1, rank_2, file_2);
                        if(valid == 1 && rank_1 == 0 && file_1 == 0)
                            r3 = 1;
                        else if(valid == 1 && rank_1 == 0 && file_1 == 7)
                            r4 = 1;
                        break;
                    case 'N':
                        valid = knight(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'B':
                        valid = bishop(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'Q':
                        valid = Queen(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'K':
                        valid = king(rank_1, file_1, rank_2, file_2); //if the king moved save this move
                        if (valid == 1) //save the
                            {
                                B_rank = rank_2;
                                B_file = file_2;
                                B_moved = 1;
                            }
                        break;
                    case 'P':
                        valid = pawn(rank_1, file_1, rank_2, file_2);
                        break;
                    default:
                        printf("you choose invalid piece\n");

                }
                if(valid)
                {
                    //make history for the moves
                    moves[steps].rank1 = rank_1;
                    moves[steps].file1 = file_1;
                    moves[steps].piece1 = chess_board[rank_1][file_1];
                    moves[steps].rank2 = rank_2;
                    moves[steps].file2 = file_2;
                    moves[steps].piece2 = chess_board[rank_2][file_2];

                    //taking out the dead pieces
                    if(chess_board[rank_2][file_2] != i && chess_board[rank_2][file_2] != j)
                    {
                        moves[steps].out = 1;
                        if(out_w == 4) //to move between rows
                            out_rows_w ++;
                        if(out_w > 3)
                            out_w %= 4; //the row can take only 4 pieces
                        out_pieces[7 - out_rows_w][out_w] = chess_board[rank_2][file_2]; //move it next to the board
                        out_w++;//counting the out white pieces

                    }
                    //move the piece
                    chess_board[rank_2][file_2] = chess_board[rank_1][file_1];
                    chess_board[rank_1][file_1] = tmp_chess[rank_1][file_1];
                    //in case there was any promotion
                    if((chess_board[rank_2][file_2] == p && rank_2 == 0) ||(chess_board[rank_2][file_2] == P && rank_2 == 7))
                    {
                        print_chess_board();
                        promotion(chess_board[rank_2][file_2], rank_2, file_2);
                    }
                    steps++;
                    //prevent ant move that don't protect the king in case of check
                    if(check_BLACK(B_rank, B_file) == 0)
                    {
                        printf("you should protect your king\n");
                        delay(1500);
                        undo();
                    }
                }
                else
                {
                    printf("Invalid move, enter another valid move: ");
                    gets(position);
                    move_piece(position);
                }
            }
            else
            {
                printf("Invalid move, enter another valid move: ");
                gets(position);
                move_piece(position);
            }
            //look for checkmate
            chek_mate_w ();
            save_1=chek_mate_w ();
            break;
        default:
            printf("invalid user\n");
    }
}

/**************************************************function to each piece******************************************/
/*********************************************************ROOK MOVEMENT FUNCTION**********************************************/
int rook (int rank_1, int file_1, int rank_2, int file_2)
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
/*********************************************************BISHOP MOVEMENT FUNCTION**********************************************/
int bishop (int rank_1, int file_1, int rank_2, int file_2)
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
/*********************************************************KNIGHT MOVEMENT FUNCTION**********************************************/
int knight(int rank_1, int file_1, int rank_2, int file_2 )
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

/*********************************************************QUEEN MOVEMENT FUNCTION**********************************************/
int Queen (int rank_1,int file_1,int rank_2,int file_2)
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

/*********************************************************KING MOVEMENT FUNCTION**********************************************/
int king(int rank_1, int file_1, int rank_2, int file_2)
{
    int x = abs(rank_1 - rank_2);
    int y = abs(file_1 - file_2);
    //the king can move only one step in any direction
    if(x == 1 || y == 1)
        return 1;
    else if(x == 0 && y == 2)
        return castling(rank_1, file_1, rank_2, file_2);
    else
        return 0;
}

/*********************************************************CASTLING FUNCTION***************************************************/
int castling(int rank_1, int file_1, int rank_2, int file_2)
{
    if(W_moved == 0 && r1 == 0 && rank_2 == 7 &&file_2 == 2 && chess_board[7][3] == j && chess_board[7][2] == i && chess_board[7][1] == j && check_white(W_rank, W_file) == 1)
    {
        moves[steps].rank1 = 7;
        moves[steps].file1 = 0;
        moves[steps].piece1 = r;
        moves[steps].rank2 = 7;
        moves[steps].file2 = 3;
        moves[steps].piece2 = j;
        steps++;

        chess_board[7][3] = r;
        chess_board[7][0] = tmp_chess[7][0];
        return 1;
    }
    else if(W_moved == 0 && r2 == 0 && chess_board[7][5] == j && chess_board[7][6] == i && check_white(W_rank, W_file) == 1)
    {
        moves[steps].rank1 = 7;
        moves[steps].file1 = 7;
        moves[steps].piece1 = r;
        moves[steps].rank2 = 7;
        moves[steps].file2 = 5;
        moves[steps].piece2 = j ;
        steps++;

        chess_board[7][5] = r;
        chess_board[7][7] = tmp_chess[7][7];
        return 1;
    }
    else if(B_moved == 0 && r3 == 0 && chess_board[0][3] == i && chess_board[0][2] == j && chess_board[0][1] == i && check_BLACK(B_rank, B_file) == 1)
    {
        moves[steps].rank1 = 0;
        moves[steps].file1 = 0;
        moves[steps].piece1 = R;
        moves[steps].rank2 = 0;
        moves[steps].file2 = 3;
        moves[steps].piece2 = i;
        steps++;

        chess_board[0][3] = R;
        chess_board[0][0] = tmp_chess[0][0];
        return 1;
    }
    else if(B_moved == 0 && r4 == 0 && chess_board[0][5] == i && chess_board[0][6] == j && check_BLACK(B_rank, B_file) == 1)
    {
        moves[steps].rank1 = 0;
        moves[steps].file1 = 7;
        moves[steps].piece1 = R;
        moves[steps].rank2 = 0;
        moves[steps].file2 = 5;
        moves[steps].piece2 = i;
        steps++;

        chess_board[0][5] = R;
        chess_board[0][7] = tmp_chess[0][7];
        return 1;
    }
    else
        return 0;

}

/*********************************************************PAWN MOVEMENT FUNCTION**********************************************/
int pawn(int rank_1, int file_1, int rank_2, int file_2)
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
/*********************************************************EN PASSANT FUNCTION*************************************************/
int en_passant(int rank_1, int file_1, int rank_2, int file_2)
{

}

/*********************************************************PROMOTION FUNCTION**************************************************/
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
/*********************************************************DEAD POSITIONS******************************************************/
int check_draw()
{
    int ro = 0, ni = 0, bi = 0, qu = 0, ki = 0, pa = 0, place[2];
    ////black  player
         int o_pices;
        for (int i =0;i<4;i++)
        {
            for (int j =0;j<4;j++)
            {
                if(out_pieces[i][j]==o)
                     o_pices ++;
            }
        }

                //// white player
        int w_pices;
        for (int i =4;i<8;i++)
        {
            for (int j = 0;j<4;j++)
            {
                if(out_pieces[i][j]==o)
                    w_pices++;
            }
        }

    for(int rank = 0; rank < 8; rank++)
    {
        for(int file = 0; file < 8; file++)
        {
            if(chess_board[rank][file] == r || chess_board[rank][file] == R)
                ro++;
            else if(chess_board[rank][file] == n || chess_board[rank][file] == N)
                ni++;
            else if(chess_board[rank][file] == b || chess_board[rank][file] == B)
            {
                bi++;
                if(bi <= 2)
                place[bi - 1] = chess_board[rank][file];
            }
            else if(chess_board[rank][file] == q || chess_board[rank][file] == Q)
                qu++;
            else if(chess_board[rank][file] == k || chess_board[rank][file] == K)
                ki++;
            else if(chess_board[rank][file] == p || chess_board[rank][file] == P)
                pa++;
        }
    }
    if(ro == 0 && ni == 0 && bi == 0 && qu == 0 && ki == 2 && pa == 0)
        return 1;
    else if(ro == 0 && ni == 1 && bi == 0 && qu == 0 && ki == 2 && pa == 0)
        return 1;
    else if(ro == 0 && ni == 0 && bi == 1 && qu == 0 && ki == 2 && pa == 0)
        return 1;
    else if(ro == 0 && ni == 0 && bi == 2 && qu == 0 && ki == 2 && pa == 0 && place[0] == place[1])
        return 1;
        // stalemate part
    else if(o_pices == 1)
    {
            if (check_BLACK(B_rank+1,B_file)==0&&check_BLACK(B_rank-1,B_file-1)==0&&
                check_BLACK(B_rank,B_file-1)==0&&check_BLACK(B_rank+1,B_file-1)==0&&
                check_BLACK(B_rank-1,B_file)==0&&check_BLACK(B_rank-1,B_file+1)==0)
            {
                return 1;
            }
    }
    else if (w_pices == 1)
    {
            if (check_white(B_rank+1,B_file)==0&&check_white(B_rank-1,B_file-1)==0&&
                check_white(B_rank,B_file-1)==0&&check_white(B_rank+1,B_file-1)==0&&
                check_white(B_rank-1,B_file)==0&&check_white(B_rank-1,B_file+1)==0)
                {
                    return 1;
                }
    }
    else
        return 0;
}
/*********************************************************CHECK FUNCTION******************************************************/
/*check white king*/
int check_white (int w_k_rank ,int w_k_file)
{
    //check if any piece of the black pieces can attack the white king
    int  peace ;
    for (int i = 0; i < 8; i++)
    {
       for(int j = 0; j < 8; j++)
       {
           switch(ascii_character[chess_board[i][j]])
           {
           case'R':
                    if (rook(i, j, w_k_rank, w_k_file) == 1)
                    {
                        attak_piece_rank = i;
                        attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'Q':
                    if(Queen(i, j, w_k_rank, w_k_file) == 1)
                    {
                        attak_piece_rank = i;
                        attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'N':
                    if(knight(i, j, w_k_rank, w_k_file) == 1)
                    {
                        attak_piece_rank = i;
                        attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'B':
                    if (bishop(i, j, w_k_rank, w_k_file) == 1)
                    {
                        attak_piece_rank = i;
                        attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'P':
                    if ((i == w_k_rank - 1 && j == w_k_file - 1) || (i == w_k_rank - 1 && j == w_k_file + 1))
                    {
                        attak_piece_rank = i;
                        attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           default :
                    peace = 1;
                    break;
           }
       }
   }
   return peace;
}

/*check black king*/
int check_BLACK (int B_k_rank ,int B_k_file)
{
    //check if any white piece can attack the black king
    int  peace ;
    for (int i = 0; i < 8; i++)
    {
       for(int j = 0; j < 8; j++)
       {
           switch(ascii_character[chess_board[i][j]])
           {
           case'r':
                    if (rook(i, j, B_k_rank, B_k_file) == 1)
                    {
                        w_attak_piece_rank = i;
                        w_attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'q':
                    if (Queen(i, j, B_k_rank, B_k_file) == 1)
                    {
                        w_attak_piece_rank = i;
                        w_attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'n':
                    if (knight(i, j, B_k_rank, B_k_file) == 1)
                    {
                        w_attak_piece_rank = i;
                        w_attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'b':
                    if (bishop(i, j, B_k_rank, B_k_file) == 1)
                    {
                        w_attak_piece_rank = i;
                        w_attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'p':
                    if ((i == B_k_rank - 1 && j == B_k_file - 1) || (i == B_k_rank - 1 && j == B_k_file + 1))
                    {
                        w_attak_piece_rank = i;
                        w_attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           default :
                        peace = 1;
                     break;
           }
       }
   }
   return peace;
}
/*********************************************************CHECKMtATE FUNCTIONS************************************************/
/*check mate for white king*/
int chek_mate_w()
{
    int prob;
    int w_king_rank = W_rank, w_king_file = W_file;
    if(check_white(w_king_rank, w_king_file) == 0)
    {
        //check if we can move the king
        if(king(w_king_rank, w_king_file, w_king_rank + 1, w_king_file + 1) == 1 || king(w_king_rank, w_king_file, w_king_rank, w_king_file + 1) == 1 ||
            king(w_king_rank, w_king_file, w_king_rank + 1, w_king_file) == 1 || king(w_king_rank, w_king_file, w_king_rank - 1, w_king_file - 1) == 1 ||
            king(w_king_rank, w_king_file, w_king_rank, w_king_file - 1) == 1 || king(w_king_rank, w_king_file, w_king_rank + 1, w_king_file - 1) == 1 ||
            king(w_king_rank, w_king_file, w_king_rank - 1, w_king_file) == 1 || king(w_king_rank, w_king_file, w_king_rank - 1, w_king_file + 1) == 1)
        {
            return 1;
        }
        else if (1)
        {
            //If we can kill the piece attacking
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    switch (ascii_character[chess_board[i][j]])
                    {
                        case'r':
                            if(rook(i, j, attak_piece_rank, attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'q':
                            if(Queen(i, j, attak_piece_rank, attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'n':
                            if(knight(i, j, attak_piece_rank, attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'p':
                            if(i == attak_piece_rank + 1 && j == attak_piece_file - 1 || i == attak_piece_rank + 1 && j == attak_piece_file + 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'b':
                            if(bishop(i, j, attak_piece_rank, attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        default :
                                prob = 0;
                                break;
                    }
                    if(prob == 1)
                        break;
                }
                if(prob == 1)
                    break;
            }
        }
    }
    else
    {
        prob = 1;
    }
    return prob ;
}

/*check mate for black king*/
int chek_mate_b()
{
    int prob;
    //If we can kill the piece attacking
    int b_king_rank = B_rank, b_king_file = B_file;
    if(check_BLACK(b_king_rank, b_king_file) == 0)
    {
        if(king(b_king_rank, b_king_file, b_king_rank + 1, b_king_file + 1) == 1 || king(b_king_rank, b_king_file, b_king_rank, b_king_file + 1) == 1 ||
            king(b_king_rank, b_king_file, b_king_rank + 1, b_king_file) == 1 || king(b_king_rank, b_king_file, b_king_rank - 1, b_king_file - 1) == 1 ||
            king(b_king_rank, b_king_file, b_king_rank, b_king_file - 1) == 1 || king(b_king_rank, b_king_file, b_king_rank + 1, b_king_file - 1) == 1 ||
            king(b_king_rank, b_king_file, b_king_rank - 1, b_king_file) == 1 || king(b_king_rank, b_king_file, b_king_rank - 1, b_king_file + 1) == 1)
        {
            return 1;
        }
        else if(1) //if we can kill the piece attacking
        {
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    switch(ascii_character[chess_board[i][j]])
                    {
                        case'R':
                            if (rook(i, j, w_attak_piece_rank, w_attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'Q':
                            if(Queen(i, j, w_attak_piece_rank, w_attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'N':
                            if(knight(i, j, w_attak_piece_rank, w_attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'P':
                            if(i == w_attak_piece_rank + 1 && j == w_attak_piece_file - 1 || i == w_attak_piece_rank + 1 && j == w_attak_piece_file + 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'B':
                            if(bishop(i, j, w_attak_piece_rank, w_attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        default :
                            prob = 0;
                            break;
                    }
                    if(prob == 1)
                        break;
                }
                if(prob == 1)
                    break;
            }
        }
    }
    else
    {
        prob = 1;
    }
    return prob ;
}
/*********************************************************UNDO / REDO FUNCTIONS***********************************************/
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
        chess_board[moves[steps].rank1][moves[steps].file1] = tmp_chess[moves[steps].rank1][moves[steps].file1];
        //change turns
        if(turn == 2)
            turn = 1;
        else
            turn = 2;

        undo_counter --; steps++;
    }
    else if(undo_counter > 0 && moves[steps].out == 1)
    {
        //re-move the piece like before undo
        out_pieces[moves[steps].rank_out][moves[steps].file_out] = chess_board[moves[steps].rank2][moves[steps].file2];
        chess_board[moves[steps].rank2][moves[steps].file2] = chess_board[moves[steps].rank1][moves[steps].file1];
        chess_board[moves[steps].rank1][moves[steps].file1] = tmp_chess[moves[steps].rank1][moves[steps].file1];
        //change turns
        if(turn == 2)
            turn = 1;
        else
            turn = 2;

        undo_counter --; steps++;
    }
    else
    {
        printf("REDO is not available");
        delay(1500); //delay some time to read the last message
    }
}

//function to delay some seconds to use it to show some messages
void delay(int d)
{
    //empty nested loop to waste some time
    for(int i = 0; i < d * 50; i++)
    {
        for(int j = 0; j < d * 10; j++){}
    }
}
