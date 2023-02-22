#include <cs50.h>
#include <stdio.h>

void brick(int bricks);
void spaces(int spaces, int bricks);

int main(void)
{
    int bricks = 0;
    int height = 0;
    while(height<1)
    {
        height = get_int("Height: ");
    }

    for(int i = 0; i < height; i++)
    {
        bricks++;

        spaces(height,bricks);

        brick(bricks);

        printf("  ");

        brick(bricks);

        printf("\n");
    }

}

void brick(int bricks){
    for(int b = 0; b < bricks; b++)
        {
            printf("#");
        }
}

void spaces(int spaces, int bricks)
{
    for(int j = spaces; j > bricks; j--)
    {
        printf(" ");
    }
}