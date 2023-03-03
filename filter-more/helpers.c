#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            if (image[h][w].rgbtRed < 255 & image[h][w].rgbtBlue < 255 & image[h][w].rgbtGreen < 255)
            {
                image[h][w].rgbtRed -= 100;
                if(image[h][w].rgbtRed < 0)
                {
                    image[h][w].rgbtRed = 0;
                }
                image[h][w].rgbtBlue = image[h][w].rgbtRed;
                image[h][w].rgbtGreen = image[h][w].rgbtRed;
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
