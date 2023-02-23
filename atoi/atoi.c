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
    string test = input;

    if (input == 0)
    {
        return 0;
    }

   int value = 0;
   int length = strlen(input);
   string currentLetter = NULL;

    value = test[length - 1];

  //  for (int c = 0; c < length-1; c++)
  //  {
  //      currentLetter[c] = input[c];
  //  }

      strncpy(currentLetter, test, length-1);


    return convert(currentLetter);
}