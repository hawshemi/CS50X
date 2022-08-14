#include <stdio.h>
#include <cs50.h>


int main(void)
{
    //Getting the correct input
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    //For Loop
    for (int row = 0; row < h; row++)
    {
        //left space
        for (int space = h - row - 1; space > 0; space--)
        {
            printf(" ");
        }
        //left hashes
        for (int left_hash = 0; left_hash < row + 1; left_hash++)
        {
            printf("#");
        }
        //2space gap
        printf("  ");

        //righ hashes
        for (int right_hash = 0; right_hash < row + 1; right_hash++)
        {
            printf("#");
        }
        printf("\n");
    }

}