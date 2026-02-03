#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            BYTE gray_brightness =
                round((image[h][w].rgbtBlue + image[h][w].rgbtRed + image[h][w].rgbtGreen) / 3.0);
            image[h][w].rgbtBlue = gray_brightness;
            image[h][w].rgbtRed = gray_brightness;
            image[h][w].rgbtGreen = gray_brightness;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            // opposite_width
            int ow = width - 1 - w;
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][ow];
            image[h][ow] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*tmpimg)[width];
    tmpimg = malloc(sizeof(RGBTRIPLE) * height * width);
    if (tmpimg == NULL)
    {
        return;
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int tmpBlue = 0;
            int tmpRed = 0;
            int tmpGreen = 0;
            float counter = 0.0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (h + j - 1 >= 0 && h + j - 1 < height && w + i - 1 >= 0 && w + i - 1 < width)
                    {
                        tmpBlue += image[h + j - 1][w + i - 1].rgbtBlue;
                        tmpRed += image[h + j - 1][w + i - 1].rgbtRed;
                        tmpGreen += image[h + j - 1][w + i - 1].rgbtGreen;
                        counter++;
                    }
                }
            }

            tmpimg[h][w].rgbtBlue = round(tmpBlue / counter);
            tmpimg[h][w].rgbtRed = round(tmpRed / counter);
            tmpimg[h][w].rgbtGreen = round(tmpGreen / counter);
        }
    }
    memcpy(image, tmpimg, sizeof(RGBTRIPLE) * height * width);
    free(tmpimg);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Factor[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    RGBTRIPLE(*tmpimg)[width];
    tmpimg = malloc(sizeof(RGBTRIPLE) * height * width);
    if (tmpimg == NULL)
    {
        return;
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float GxBlue = 0;
            float GxRed = 0;
            float GxGreen = 0;
            float GyBlue = 0;
            float GyRed = 0;
            float GyGreen = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (h + j - 1 >= 0 && h + j - 1 < height && w + i - 1 >= 0 && w + i - 1 < width)
                    {
                        GxBlue += image[h + j - 1][w + i - 1].rgbtBlue * Factor[j][i];
                        GyBlue += image[h + j - 1][w + i - 1].rgbtBlue * Factor[i][j];
                        GxRed += image[h + j - 1][w + i - 1].rgbtRed * Factor[j][i];
                        GyRed += image[h + j - 1][w + i - 1].rgbtRed * Factor[i][j];
                        GxGreen += image[h + j - 1][w + i - 1].rgbtGreen * Factor[j][i];
                        GyGreen += image[h + j - 1][w + i - 1].rgbtGreen * Factor[i][j];
                    }
                }
            }

            int SobelBlue = round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            int SobelRed = round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            int SobelGreen = round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
            if (SobelBlue > 255)
                SobelBlue = 255;
            if (SobelRed > 255)
                SobelRed = 255;
            if (SobelGreen > 255)
                SobelGreen = 255;
            tmpimg[h][w].rgbtBlue = SobelBlue;
            tmpimg[h][w].rgbtRed = SobelRed;
            tmpimg[h][w].rgbtGreen = SobelGreen;
        }
    }
    memcpy(image, tmpimg, sizeof(RGBTRIPLE) * height * width);
    free(tmpimg);
    return;
}
