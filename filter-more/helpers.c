#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float red = 0;
    float blue = 0;
    float green = 0;
    float average = 0;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (image[h][w].rgbtRed < 255 || image[h][w].rgbtBlue < 255 || image[h][w].rgbtGreen < 255)
            {
                red = image[h][w].rgbtRed;
                blue = image[h][w].rgbtBlue;
                green = image[h][w].rgbtGreen;

                average = round((red + blue +  green) / 3);
                image[h][w].rgbtRed = average;
                image[h][w].rgbtBlue = average;
                image[h][w].rgbtGreen = average;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++) // Range is halving every time (0,0 -> 0,4 then 0,1 -> 0,3 then 0,2 - 0, 2 then stop)
        {
            //algorithm to switch last place with first place then second to last etc
            temp = image[h][width-(w+1)];
            image[h][width-(w+1)] = image[h][w];
            image[h][w] = temp;
        }
    }
    // switch [h][w] with [w][h]? (or maybe a start point e.g. h+current or something) (inverse of w?)
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    float  rgbtBlueTemp = 0;
    float  rgbtGreenTemp = 0;
    float  rgbtRedTemp = 0;
    float average = 0;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp[h][w] = image[h][w];
        }
    }

    for (int h1 = 0; h1 < height; h1++)
    {
        for (int w1 = 0; w1 < width; w1++)
        {
            if (h1 > 0 && h1 < height - 1 && w1 > 0 && w1 < width - 1)
            {
                rgbtRedTemp = image[h1][w1].rgbtRed;
                rgbtBlueTemp = image[h1][w1].rgbtBlue;
                rgbtGreenTemp = image[h][w].rgbtGreen;
            }

            image[h][w] = image[h][w];
            image[h][w] = temp;

    return;
        }
    }

}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
