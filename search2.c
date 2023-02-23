#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // An array of integers
    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    // Search for number
    string s = get_string("String: ");
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(strings[i], s))
        {
            printf("Found in position %i \n", i+1);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}