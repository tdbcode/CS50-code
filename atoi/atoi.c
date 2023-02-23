#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input, int length);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input, strlen(input)));
}

int convert(string input, int length)
{
    int value = 0;
    char S[length];

    for (int c = 0; c < length-1; c++)
    {
        S[c] = input[c];
    }

    if (length < 0) {
        return 0;
    }

    return convert(S, strlen(S) - 1);
}