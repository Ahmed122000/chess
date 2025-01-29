#ifndef KING_H
#define KING_H

    int validate_castling_move(int rank_1, int file_1, int rank_2, int file_2);
    int validate_king_move(int rank_1, int file_1, int rank_2, int file_2);
    int check_draw();
    int check_white (int w_k_rank ,int w_k_file);
    int check_BLACK (int B_k_rank ,int B_k_file);
    int chek_mate_w();
    int chek_mate_b();
#endif