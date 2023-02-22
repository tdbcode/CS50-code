#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("Height: ");
    int width = 1;
    for (int i = 2; i < height; i++)
    {
        width++;
        while (width <= i)
        {
            printf("#");
        }

        printf("\n");
    }
}