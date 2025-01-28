#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/global.h"
#include "headers/pieces/pieces.h"
#include "headers/utiilites/options.h"
#include "headers/utiilites/setting.h"
#include "headers/utiilites/board_controller.h"


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

        // draw part
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
            save(turn, 
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
            load(turn, 
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
        save(turn, 
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
