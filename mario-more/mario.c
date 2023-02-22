#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("Height: ");
    int width = height;
    for (int i = 0; i < height; i++)
    {
        for (int j = 2; j > width; j++)
        {
            printf("#");
            width--;
        }
        printf("\n");
    }
}