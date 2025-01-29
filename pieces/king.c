#include "../headers/global.h"
#include "../headers/pieces/pieces.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validate_king_move(int rank_1, int file_1, int rank_2, int file_2)
{
    int x = abs(rank_1 - rank_2);
    int y = abs(file_1 - file_2);
    //the king can move only one step in any direction
    if(x == 1 || y == 1)
        return 1;
    else if(x == 0 && y == 2)
        return validate_castling_move(rank_1, file_1, rank_2, file_2);
    else
        return 0;
}

/*********************************************************CASTLING FUNCTION***************************************************/
int validate_castling_move(int rank_1, int file_1, int rank_2, int file_2)
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
        chess_board[7][0] = empty_board[7][0];
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
        chess_board[7][7] = empty_board[7][7];
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
        chess_board[0][0] = empty_board[0][0];
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
        chess_board[0][7] = empty_board[0][7];
        return 1;
    }
    else
        return 0;

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
                    if (validate_rook_move(i, j, w_k_rank, w_k_file) == 1)
                    {
                        attak_piece_rank = i;
                        attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'Q':
                    if(validate_queen_move(i, j, w_k_rank, w_k_file) == 1)
                    {
                        attak_piece_rank = i;
                        attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'N':
                    if(validate_knight_move(i, j, w_k_rank, w_k_file) == 1)
                    {
                        attak_piece_rank = i;
                        attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'B':
                    if (validate_bishob_move(i, j, w_k_rank, w_k_file) == 1)
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
                    if (validate_rook_move(i, j, B_k_rank, B_k_file) == 1)
                    {
                        w_attak_piece_rank = i;
                        w_attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'q':
                    if (validate_queen_move(i, j, B_k_rank, B_k_file) == 1)
                    {
                        w_attak_piece_rank = i;
                        w_attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'n':
                    if (validate_knight_move(i, j, B_k_rank, B_k_file) == 1)
                    {
                        w_attak_piece_rank = i;
                        w_attak_piece_file = j;
                        return 0;
                    }
                    else
                        peace = 1;
                    break;
           case 'b':
                    if (validate_bishob_move(i, j, B_k_rank, B_k_file) == 1)
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
        if( validate_king_move (w_king_rank, w_king_file, w_king_rank + 1, w_king_file + 1) == 1 || 
            validate_king_move(w_king_rank, w_king_file, w_king_rank, w_king_file + 1) == 1 ||
            validate_king_move(w_king_rank, w_king_file, w_king_rank + 1, w_king_file) == 1 || 
            validate_king_move(w_king_rank, w_king_file, w_king_rank - 1, w_king_file - 1) == 1 ||
            validate_king_move(w_king_rank, w_king_file, w_king_rank, w_king_file - 1) == 1 || 
            validate_king_move(w_king_rank, w_king_file, w_king_rank + 1, w_king_file - 1) == 1 ||
            validate_king_move(w_king_rank, w_king_file, w_king_rank - 1, w_king_file) == 1 || 
            validate_king_move(w_king_rank, w_king_file, w_king_rank - 1, w_king_file + 1) == 1)
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
                            if(validate_rook_move(i, j, attak_piece_rank, attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'q':
                            if(validate_queen_move(i, j, attak_piece_rank, attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'n':
                            if(validate_knight_move(i, j, attak_piece_rank, attak_piece_file) == 1)
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
                            if(validate_bishob_move(i, j, attak_piece_rank, attak_piece_file) == 1)
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
        if( validate_king_move(b_king_rank, b_king_file, b_king_rank + 1, b_king_file + 1) == 1 || 
            validate_king_move(b_king_rank, b_king_file, b_king_rank, b_king_file + 1) == 1 ||
            validate_king_move(b_king_rank, b_king_file, b_king_rank + 1, b_king_file) == 1 || 
            validate_king_move(b_king_rank, b_king_file, b_king_rank - 1, b_king_file - 1) == 1 ||
            validate_king_move(b_king_rank, b_king_file, b_king_rank, b_king_file - 1) == 1 || 
            validate_king_move(b_king_rank, b_king_file, b_king_rank + 1, b_king_file - 1) == 1 ||
            validate_king_move(b_king_rank, b_king_file, b_king_rank - 1, b_king_file) == 1 || 
            validate_king_move(b_king_rank, b_king_file, b_king_rank - 1, b_king_file + 1) == 1)
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
                            if (validate_rook_move(i, j, w_attak_piece_rank, w_attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'Q':
                            if(validate_queen_move(i, j, w_attak_piece_rank, w_attak_piece_file) == 1)
                            {
                                prob = 1;
                                break;
                            }
                            else
                                prob = 0;
                            break;
                        case 'N':
                            if(validate_knight_move(i, j, w_attak_piece_rank, w_attak_piece_file) == 1)
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
                            if(validate_bishob_move(i, j, w_attak_piece_rank, w_attak_piece_file) == 1)
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