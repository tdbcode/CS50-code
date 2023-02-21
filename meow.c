#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int i = 0;
    while (i <3)
    {
        printf("meow\n");
        i++;
    }

    i = 3;
    while(i>0)
    {
        printf("woem\n");
        i--;
    }

    for (int j = 0; j<3; j++)
    {
        printf("meow\n");
    }

    while(true)
    {
        printf("meow\n");
    }
}