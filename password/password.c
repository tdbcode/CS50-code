// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool upperc = false;
    bool lowerc = false;
    bool number = false;
    bool symbol = false;
    for (int c = 0; c < strlen(password); c++)
    {
        char temp = password[c];
        if (isupper(temp))
        {
            upperc = true;
        }
        else if (islower(temp))
        {
            lowerc = true;
        }
        else if (isdigit(temp))
        {
            number = true;
        }
        else if (ispunct(temp))
        {
            symbol = true;
        }
    }

    if (upperc && lowerc && number && symbol)
    {
        return true;
    }
    else
    {
        return false;
    }
}
