#include <stdio.h>
#include <stdlib.h>


#include "../headers/global.h"
#include "../headers/pieces/pieces.h"
#include "../headers/utilities/delay.h"
#include "../headers/utilities/options.h"

/*print the chess board*/
void print_chess_board()
{
    //to clear the screen after each output
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Linux/macOS
    #endif

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
                        valid = validate_rook_move(rank_1, file_1, rank_2, file_2);
                        if(valid == 1 && rank_1 == 7 && file_1 == 0)
                            r1 = 1;
                        else if(valid == 1 && rank_1 == 7 && file_1 == 7)
                            r2 = 1;
                        break;
                    case 'n':
                        valid = validate_knight_move(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'b':
                        valid = validate_bishob_move(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'q':
                        valid = validate_queen_move(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'k':
                        valid = validate_king_move(rank_1, file_1, rank_2, file_2);
                        if (valid == 1) //if the king moved save this move
                            {
                                W_rank = rank_2;
                                W_file = file_2;
                                W_moved = 1;
                            }
                        break;
                    case 'p':
                        valid = validate_pawn_move(rank_1, file_1, rank_2, file_2);
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
                    chess_board[rank_1][file_1] = empty_board[rank_1][file_1];
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
                        valid = validate_rook_move(rank_1, file_1, rank_2, file_2);
                        if(valid == 1 && rank_1 == 0 && file_1 == 0)
                            r3 = 1;
                        else if(valid == 1 && rank_1 == 0 && file_1 == 7)
                            r4 = 1;
                        break;
                    case 'N':
                        valid = validate_knight_move(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'B':
                        valid = validate_bishob_move(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'Q':
                        valid = validate_queen_move(rank_1, file_1, rank_2, file_2);
                        break;
                    case 'K':
                        valid = validate_king_move(rank_1, file_1, rank_2, file_2); //if the king moved save this move
                        if (valid == 1) //save the
                            {
                                B_rank = rank_2;
                                B_file = file_2;
                                B_moved = 1;
                            }
                        break;
                    case 'P':
                        valid = validate_pawn_move(rank_1, file_1, rank_2, file_2);
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
                    chess_board[rank_1][file_1] = empty_board[rank_1][file_1];
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
