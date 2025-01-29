#include "../headers/utilities/delay.h"


void delay(int d)
{
    //empty nested loop to waste some time
    for(int i = 0; i < d * 50; i++)
    {
        for(int j = 0; j < d * 10; j++){}
    }
}