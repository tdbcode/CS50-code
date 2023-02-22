// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string argv[]);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Missing command-line argument\n");
        return 1;
    }

    printf("%s\n", replace(argv));

    return 0;


}

string replace(string argv[]){

    char temp;
    for(int c = 0; c < strlen(argv[1]); c++)
    {
        temp = argv[1][c];

        switch (temp)
        {
            case 'a':
                argv[1][c] = '6';
                break;
            case 'e':
                argv[1][c] = '3';
                break;
            case 'i':
                argv[1][c] = '1';
                break;
            case 'o':
                argv[1][c] = '0';
                break;
        }
    }
    return argv[1];
}
