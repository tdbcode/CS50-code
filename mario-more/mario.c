#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("Height: ");
    int bricks = 0;

    for(int i = 0; i < height; i++)
    {
        bricks++;
        for(int j = height; j > bricks; j--)
        {
            printf(" ");
        }

        for(int b = 0; b < bricks; b++)
        {
            printf("#");
        }

        printf("  ");

        printf("\n");
    }

}