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
            temp = image[h][width - (w + 1)];
            image[h][width - (w + 1)] = image[h][w];
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
    int counter = 0;

    for (int h = 0; h < height; h++) // copy array to temp array
    {
        for (int w = 0; w < width; w++)
        {
            temp[h][w] = image[h][w];
        }
    }

    for (int h1 = 0; h1 < height; h1++) // get current pixel in temp array
    {
        for (int w1 = 0; w1 < width; w1++) // get current pixel in temp array
        {
            // Now need to select up and down but only if not edge pixels
            // this does up
            counter = 0;
            rgbtRedTemp = 0;
            rgbtBlueTemp = 0;
            rgbtGreenTemp = 0;
            for (int i = -1; i < 2; i++)
            {
                // this does across
                for (int j = -1; j < 2; j++)
                {
                    // can make a for loop skip a step using continue, reference : https://www.freecodecamp.org/news/c-break-and-continue-statements-loop-control-statements-in-c-explained/#:~:text=In%20C%2C%20if%20you%20want%20to%20skip%20iterations%20in%20which,which%20the%20condition%20is%20true.
                    if (h1 + i < 0 || h1 + i >= height)
                    {
                        continue;
                    }

                    if (w1 + j < 0 || w1 + j >= width)
                    {
                        continue;
                    }
                    // need to offset each pixel for calculation in array - so current pixel (height-1 width-1, height-1 width, height -1 width+1)
                    // (then height width -1, height width, height width +1, then height + 1 width - 1, height + 1 width, height +1 width +1)
                    rgbtRedTemp += image[h1 + i][w1 + j].rgbtRed; // get sum of all red
                    rgbtBlueTemp += image[h1 + i][w1 + j].rgbtBlue; // get sum of all blue
                    rgbtGreenTemp += image[h1 + i][w1 + j].rgbtGreen; // get sum of all green
                    counter++;
                }
                temp[h1][w1].rgbtRed = round(rgbtRedTemp / counter); // do average of all 9 pixels for red
                temp[h1][w1].rgbtGreen = round(rgbtGreenTemp /
                                               counter); // what if there aren't nine pixels, e.g. top left, bottom right, etc, use counter
                temp[h1][w1].rgbtBlue = round(rgbtBlueTemp / counter);
            }

        }
    }

    for (int h2 = 0; h2 < height; h2++) // copy temp array back to main image array
    {
        for (int w2 = 0; w2 < width; w2++)
        {
            image[h2][w2] = temp[h2][w2];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    float  rgbtBlueTemp = 0;
    float  rgbtGreenTemp = 0;
    float  rgbtRedTemp = 0;
    int counter = 0;
    int muliplierArray = {-1, 0, 1}{-2, 0, 2}{-1, 0, 1};

    for (int h = 0; h < height; h++) // copy array to temp array
    {
        for (int w = 0; w < width; w++)
        {
            temp[h][w] = image[h][w];
        }
    }

    for (int h1 = 0; h1 < height; h1++) // get current pixel in temp array
    {
        for (int w1 = 0; w1 < width; w1++) // get current pixel in temp array
        {
            // Now need to select up and down but only if not edge pixels
            // this does up
            counter = 0;
            rgbtRedTemp = 0;
            rgbtBlueTemp = 0;
            rgbtGreenTemp = 0;
            mulitplier = 0;
            for (int i = -1; i < 2; i++)
            {
                // this does across
                for (int j = -1; j < 2; j++)
                {
                    // can make a for loop skip a step using continue, reference : https://www.freecodecamp.org/news/c-break-and-continue-statements-loop-control-statements-in-c-explained/#:~:text=In%20C%2C%20if%20you%20want%20to%20skip%20iterations%20in%20which,which%20the%20condition%20is%20true.
                    if (h1 + i < 0 || h1 + i >= height)
                    {
                        continue;
                    }

                    if (w1 + j < 0 || w1 + j >= width)
                    {
                        continue;
                    }

                    if (h1 + i == 0 & w1 + j == 0)
                    {
                        muliplier = 2;
                    }
                    else if (h1 + i == -1 ||  j + i == 1)
                    {
                        muliplier = 0;
                    }
                    // need to offset each pixel for calculation in array - so current pixel (height-1 width-1, height-1 width, height -1 width+1)
                    // (then height width -1, height width, height width +1, then height + 1 width - 1, height + 1 width, height +1 width +1)
                    rgbtRedTemp += image[h1 + i][w1 + j].rgbtRed; // get sum of all red
                    rgbtBlueTemp += image[h1 + i][w1 + j].rgbtBlue; // get sum of all blue
                    rgbtGreenTemp += image[h1 + i][w1 + j].rgbtGreen; // get sum of all green
                    counter++;
                }
                temp[h1][w1].rgbtRed = round(rgbtRedTemp / counter); // do average of all 9 pixels for red
                temp[h1][w1].rgbtGreen = round(rgbtGreenTemp /
                                               counter); // what if there aren't nine pixels, e.g. top left, bottom right, etc, use counter
                temp[h1][w1].rgbtBlue = round(rgbtBlueTemp / counter);
            }

        }
    }

    for (int h2 = 0; h2 < height; h2++) // copy temp array back to main image array
    {
        for (int w2 = 0; w2 < width; w2++)
        {
            image[h2][w2] = temp[h2][w2];
        }
    }
    return;
}
