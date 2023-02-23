#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // An array of integers
    string names[] = {"Carter", "David"};
    string numbers[] = {"+1-617-495-1000", "+1-949-468-2750"};

    // Search for number
    string name = get_string("Name: ");
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(names[i], name) == 0)
        {
            printf("Found in position %i : %s \n", i+1, numbers[i]);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}