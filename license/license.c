#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7]; // Buffer from the file

    // Create array to store plate numbers
    char *plates[8]; // A string of 8 pointers

    for (int i = 0; i < 7; i++){
        plates [i] = malloc(7);
    }

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;
    char *s = NULL;
    while (fread(buffer, 1, 7, infile) == 7)
    {
        s
        // Replace '\n' with '\0'
        buffer[6] = '\0';
        s = &buffer[0];

        // Save plate number in array
        strcpy(&s[0],&plates[idx]);
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%c\n", plates[i]);
    }
}
