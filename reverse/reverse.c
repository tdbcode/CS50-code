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
    int headersize = sizeof(WAVHEADER); // Get header size
    WAVHEADER header;
    fread(&header, headersize, 1, input); // Load header from input file using header size

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
    fwrite(&header, headersize, 1, output);  // Write header to output file using header size

    // Use get_block_size to calculate size of block
    int blocksize = get_block_size(header);

    // Write reversed audio to file
    BYTE currentSample[blocksize];  // Temp sample for reading and writing limited to block size of each sample
    fseek(input, blocksize, SEEK_END); // Go to end of file + blocksize (4) so that when the loop is run it works back by 2
    // int currentLocator = ftell(input); // for testing purposes (was used before not unneeded in the end)
    // printf("Blocksize: %u\n", blocksize); // for testing purposes
    // printf("First Sample: %i\n", headersize); // for testing purposes
    // printf("Current Locator: %i\n", currentLocator); // for testing purposes
    //printf("File Size: %i\n", filesize); // for testing purposes

    // While the location in the file minus block size is more than header size continue to run the algorithm
    while (ftell(input) - blocksize > headersize)
    {
        fseek(input, - 2 * blocksize, SEEK_CUR); // Take current location and move it back 2 blocks
        fread(&currentSample, blocksize, 1, input); // Read in the current block from the input file
        fwrite(&currentSample, blocksize, 1, output); // Write block to output file.
        // currentLocator -= blocksize; // for testing purposes / prior attempt
    }
    // printf("Ftell: %ld\n", ftell(input)); // for testing purposes

    // close streams
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