#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SETTING_H
#define SETTING_H


void save(
    int turn, 
    int out_rows_w, 
    int out_w, 
    int out_rows_b, 
    int out_b, 
    int W_moved, 
    int B_moved, 
    int r1, 
    int r2, 
    int r3, 
    int r4
    );


void load(
    int turn, 
    int out_rows_w, 
    int out_w, 
    int out_rows_b, 
    int out_b, 
    int W_moved, 
    int B_moved, 
    int r1, 
    int r2, 
    int r3, 
    int r4
    );
#endif