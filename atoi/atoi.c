#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

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
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int value = 0;
    int length = strlen(input);
    printf("%s\n", input);

    value = input[length - 1];
    if (input[length - 1] == '&')
    {
        input[length - 1] = '\0';
    }
    printf("%szn", input);
    return 0;
    //return convert(input + length - 1);
}