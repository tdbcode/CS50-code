#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input, int length);

int main(void)
{
    string input = get_string("Enter a positive integer: ");
    char S[strlen(input)];

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
        else
        {
            S[i] = input[i];
        }
    }

    // Convert string to int
    printf("%i\n", convert(S, strlen(input)));

}

int convert(char[] input, int length)
{

    if (length < 0) {
        return 0;
    }

    return convert(S, strlen(S) - 1);
}