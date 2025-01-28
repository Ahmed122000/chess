#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/utiilites/setting.h"
#include "../headers/global.h"


/*save function*/
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
    )
{
    //save the main board
    FILE* save_board; // file to save the data
    //check that the file exists
    if((save_board = fopen(".board_data.bin", "wb")) == NULL)
    {
        printf("Cannot open file.\n");
    }
    //write the data into the file
    if(fwrite(chess_board, sizeof(int), 8*8, save_board) != 8*8)
        printf("File write error.");
    fclose(save_board); //close the file after finishing writing

    //save the out pieces
    FILE* save_out; // file to save the data
    //check that the file exits
    if((save_out = fopen(".out_data.bin", "wb")) == NULL)
    {
        printf("Cannot open file.\n");
    }
    //write the data into the file
    if(fwrite(out_pieces, sizeof(int), 8*4, save_out) != 8*4)
        printf("File write error.");
    fclose(save_out); //close the file after finishing writing

    //save the important numeric values in the code
    FILE* save_numericData;
     // open the file in write mode
    save_numericData = fopen(".nummericData.bin", "wb");
    if (save_numericData == NULL)
    {
        printf("cannot open the file\n");
    }
    fprintf(save_numericData, "%d %d %d %d %d %d %d %d %d %d %d", turn, out_w, out_rows_w, out_rows_b, out_b, W_moved, B_moved, r1, r2, r3, r4); //save the numeric values
    fclose(save_numericData); //close the file
}


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
    )
{
    FILE* load_board; // file to load the game
    if((load_board = fopen(".board_data.bin", "rb")) == NULL)//open the file and check if there any error
    {
        printf("Cannot open file.\n");
    }
    //read the data from the file
    if(fread(chess_board, sizeof(int), 8*8, load_board) != 8*8)
    {
        if(feof(load_board)) //end of the file
            printf("Premature end of file.");
        else //in case any error
            printf("File read error.");
    }
    fclose(load_board); //close the file after finish reading the data from it

    //file to load the out pieces
    FILE* load_out; // file to load the data
    if((load_out = fopen(".out_data.bin", "rb")) == NULL) //open the file and check if there any error
    {
        printf("Cannot open file.\n");
    }
    if(fread(out_pieces, sizeof(int), 8*4, load_out) != 8*4) //read the board
    {
        if(feof(load_out)) //end of the file
            printf("Premature end of file.");
        else    //in case any error
            printf("File read error.");
    }
    fclose(load_out); //close the file after loading the boards

    //load the numeric data
    FILE* load_numericData;
    // open the file in reading mode to read saved info
    load_numericData = fopen(".nummericData.bin", "r");

    if (load_numericData == NULL) //in case there was any error while opening the file
    {
        printf("cannot open the file\n");
    }
    fscanf(load_numericData, "%d %d %d %d %d %d %d %d %d %d %d", &turn, &out_rows_w, &out_w, &out_rows_b, &out_b, &W_moved, &B_moved, &r1, &r2, &r3, &r4); //read the numeric values that was saved
    fclose(load_numericData); //close the file after reading the information from it
}