#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculate value of pixels
            double average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            //set value of pixels
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculate value of pixels
            double sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            double sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            double sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;

            //make sure values arn't too high
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            //set valiue of pixels
            image[i][j].rgbtBlue = round(sepiaBlue);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtRed = round(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //store pixel
            RGBTRIPLE temp = image[i][j];

            //switch pixels
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //initalize temp variables
            double blue = 0.0;
            double green = 0.0;
            double red = 0.0;

            int c;
            int g;
            int count = 0;

            //Check to see if on corner or edge, and adjust starting point
            if ((i == 0 && j == 0) || i == 0)
            {
                c = 0;
            }
            else
            {
                c = -1;
            }

            //Calculate blur for each row
            for (; c <= 1 && !(i == (height - 1) && c == 1); c++)
            {

                //Check to see if on corner or edge, and adjust starting point
                if ((i == 0 && j == 0) || j == 0)
                {
                    g = 0;
                }
                else
                {
                    g = -1;
                }

                //Claculate blur for each columm
                for (; g <= 1 && !(j == (width - 1) && g == 1); g++)
                {
                    blue += image[i + c][j + g].rgbtBlue + 0.0;
                    green += image[i + c][j + g].rgbtGreen + 0.0;
                    red += image[i + c][j + g].rgbtRed + 0.0;

                    count++;
                }
            }

            //Round Values and save in temp
            tempImage[i][j].rgbtBlue = round(blue / count);
            tempImage[i][j].rgbtGreen = round(green / count);
            tempImage[i][j].rgbtRed = round(red / count);
        }
    }

    //Save to final image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tempImage[i][j];
        }
    }

    return;
}
