#include "helpers.h"
#include <math.h>

const int RGBSIZE = 3;
void copy_image(int height, int width, RGBTRIPLE img[height][width],
                RGBTRIPLE temp_image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int grey;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // represents the exact pixel which is being changed
            grey = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) /
                         (float) RGBSIZE);
            image[i][j].rgbtBlue = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtRed = grey;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp_pixel;
    //
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Saves the values of the pixel in the opposite part of the row
            temp_pixel = image[i][width - j - 1];
            image[i][width - j - 1] = image[i][j];
            image[i][j] = temp_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a temporary copy of the original image
    RGBTRIPLE temp_image[height][width];
    copy_image(height, width, image, temp_image);

    int values_count;
    int red;
    int green;
    int blue;
    int new_i;
    int new_j;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initializes for each specific pixel
            red = 0, green = 0, blue = 0;
            values_count = 0;

            // contiguos i,j values arround the pixel
            for (int ci = -1; ci <= 1; ci++)
            {
                for (int cj = -1; cj <= 1; cj++)
                {
                    new_i = i + ci;
                    new_j = j + cj;

                    if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width)
                    {
                        // add each value for future average
                        red += temp_image[new_i][new_j].rgbtRed;
                        green += temp_image[new_i][new_j].rgbtGreen;
                        blue += temp_image[new_i][new_j].rgbtBlue;
                        values_count++;
                    }
                }
            }
            image[i][j].rgbtRed = round((float) red / values_count);
            image[i][j].rgbtGreen = round((float) green / values_count);
            image[i][j].rgbtBlue = round((float) blue / values_count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create a temporary copy of the original image
    RGBTRIPLE temp_image[height][width];
    copy_image(height, width, image, temp_image);

    // initialize values of gx matrix colors
    int gx_red;
    int gx_green;
    int gx_blue;
    // initialize values of gy matrix colors
    int gy_red;
    int gy_green;
    int gy_blue;
    // indexes that are going to be used
    int new_i;
    int new_j;

    // the weights on the convolutional matrices
    const int DIM = 3;
    int gx[DIM][DIM] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[DIM][DIM] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initializes for each specific pixel
            gx_red = 0, gx_green = 0, gx_blue = 0;
            gy_red = 0, gy_green = 0, gy_blue = 0;

            // contiguos i,j values arround the pixel
            for (int ci = -1; ci <= 1; ci++)
            {
                for (int cj = -1; cj <= 1; cj++)
                {
                    new_i = i + ci;
                    new_j = j + cj;

                    if (new_i >= 0 && new_i < height && new_j >= 0 && new_j < width)
                    {
                        // add each weighted value for gx
                        gx_red += (temp_image[new_i][new_j].rgbtRed) * gx[ci + 1][cj + 1];
                        gx_green += (temp_image[new_i][new_j].rgbtGreen) * gx[ci + 1][cj + 1];
                        gx_blue += (temp_image[new_i][new_j].rgbtBlue) * gx[ci + 1][cj + 1];

                        // add each weithted value for gy
                        gy_red += (temp_image[new_i][new_j].rgbtRed) * gy[ci + 1][cj + 1];
                        gy_green += (temp_image[new_i][new_j].rgbtGreen) * gy[ci + 1][cj + 1];
                        gy_blue += (temp_image[new_i][new_j].rgbtBlue) * gy[ci + 1][cj + 1];
                    }
                }
            }
            // Calculate the final values of the colors
            int finalRed = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            int finalGreen = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            int finalBlue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));
            // Limitar los valores a 255
            image[i][j].rgbtRed = (finalRed > 255) ? 255 : finalRed;
            image[i][j].rgbtGreen = (finalGreen > 255) ? 255 : finalGreen;
            image[i][j].rgbtBlue = (finalBlue > 255) ? 255 : finalBlue;
        }
    }
    return;
}

void copy_image(int height, int width, RGBTRIPLE img[height][width],
                RGBTRIPLE temp_image[height][width])
{
    // Copiar cada pixel de img a temp_image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp_image[h][w] = img[h][w];
        }
    }
}
