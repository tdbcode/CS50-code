#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE *image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE currentTriple = &image[h][w];
            if (currentTriple.rgbtRed < 255 & currentTriple.rgbtBlue < 255 & currentTriple.rgbtGreen < 255)
            {
                currentTriple.rgbtRed -= 100;
                if(currentTriple.rgbtRed < 0)
                {
                    currentTriple.rgbtRed = 0;
                }
                currentTriple.rgbtBlue = currentTriple.rgbtRed;
                currentTriple.rgbtGreen = currentTriple.rgbtRed;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
