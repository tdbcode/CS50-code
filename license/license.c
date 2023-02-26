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
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    // Allocate the memory first
    for (int p = 0; p < 8; p++)
    {
        plates[p] = malloc(sizeof(buffer));
        plates[p] = fread(buffer, 1, 7, infile);
    }



    int idx = 0;

/*    while (fread(buffer, 1, 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Save plate number in array
        plates[idx] = buffer;
        idx++;
    }*/

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }
}
