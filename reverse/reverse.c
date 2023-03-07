#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // Check command-line arguments
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav \n");
        return 1;
    }

    // Open input file for reading
    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    check_format(header);

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    int blocksize = get_block_size(header);

    // Write reversed audio to file
    int firstSample = sizeof(header);

    WORD currentSample[blocksize];
    fseek(input, 0, SEEK_END);
    int currentLocator = ftell(input);
    printf("Blocksize: %u\n", blocksize);
    printf("First Sample: %i\n", firstSample);
    printf("Current Locator: %i\n", currentLocator);
    //printf("File Size: %i\n", filesize);
    printf("Ftell: %ld\n", ftell(input));

    while (currentLocator > firstSample)
    {
        printf("Ftell: %ld\n", ftell(input));
        fread(&currentSample, blocksize, 1, input);
        fwrite(&currentSample, blocksize, 1, output);
        fseek(input, currentLocator, SEEK_SET);
        currentLocator -= (blocksize);
    }

    fclose(input);
    fclose(output);
    return 0;
}

int check_format(WAVHEADER header)
{
    char wave[] = "WAVE";
    char format[4];

    for (int i = 0; i < 4; i++)
    {
        format[i] = header.format[i];
    }

    if (strcmp(format, wave))
    {
        return 0;
    }
    else
    {
        printf("Invalid file format.\n");
        return 1;
    }
}

int get_block_size(WAVHEADER header)
{
    int bytesPerSample = header.bitsPerSample / 8;
    int blocksize = bytesPerSample * header.numChannels;
    return blocksize;
}