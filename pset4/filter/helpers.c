#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum;
    float avg;

    // scroll vertical and select the line
    for (int h = 0; h < height; h++)
    {
        // scroll horizontally and select the pixel
        for (int w = 0; w < width; w++)
        {
            sum = image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue;
            avg = sum / 3.0;
            image[h][w].rgbtRed = round(avg);
            image[h][w].rgbtGreen = round(avg);
            image[h][w].rgbtBlue = round(avg);
        }
    }
    return;
}




// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // scroll vertical and select the line
    for (int h = 0; h < height; h++)
    {
        // scroll horizontally only half and swap the pixels
        for (int w = 0; w < (width / 2); w++)
        {
            RGBTRIPLE tmp = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = tmp;
        }
    }
    return;
}




// Calculate the average 3x3 box and return a blurred pixel
RGBTRIPLE calc_blur_avg(int h, int height, int w, int width, RGBTRIPLE image[height][width])
{
    // Initialise the variables
    int sum_r = 0, sum_g = 0, sum_b = 0;
    int h_min = -1, h_max = 1;
    int w_min = -1, w_max = 1;
    float cells_count = 0.0;

    RGBTRIPLE blur_pixel;

    // first row
    if (h == 0)
    {
        h_min = 0;
    }

    // last row
    if (h == height - 1)
    {
        h_max = 0;
    }

    // first column
    if (w == 0)
    {
        w_min = 0;
    }

    // last column
    if (w == width - 1)
    {
        w_max = 0;
    }


    for (int i = h_min; i <= h_max; i++)
    {
        for (int j = w_min; j <= w_max; j++)
        {
            sum_r += image[h + i][w + j].rgbtRed;
            sum_g += image[h + i][w + j].rgbtGreen;
            sum_b += image[h + i][w + j].rgbtBlue;
            cells_count += 1.0;
        }
    }

    blur_pixel.rgbtRed = round(sum_r / cells_count);
    blur_pixel.rgbtGreen = round(sum_g / cells_count);
    blur_pixel.rgbtBlue = round(sum_b / cells_count);

    return blur_pixel;
}




// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // The value of each pixel is the average of the 3x3 box around it
    RGBTRIPLE tmp_image[height][width];

    // scroll vertically
    for (int h = 0; h < height; h++)
    {
        // scroll horizontally
        for (int w = 0; w < width; w++)
        {
            tmp_image[h][w] = calc_blur_avg(h, height, w, width, image);
        }
    }

    // Copy the temporary image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = tmp_image[h][w];
        }
    }

    return;
}




// Calculate the Sobel average of 3x3 box and return a pixel
RGBTRIPLE sobel_calc(int h, int border_height, int w, int border_width, RGBTRIPLE image[border_height][border_width])
{
    // Sopbel operators
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    int sum_rx = 0, sum_ry = 0;
    int sum_gx = 0, sum_gy = 0;
    int sum_bx = 0, sum_by = 0;

    float sum_r = 0, sum_g = 0, sum_b = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sum_rx += image[h + i - 1][w + j - 1].rgbtRed * gx[i][j];
            sum_ry += image[h + i - 1][w + j - 1].rgbtRed * gy[i][j];
            sum_gx += image[h + i - 1][w + j - 1].rgbtGreen * gx[i][j];
            sum_gy += image[h + i - 1][w + j - 1].rgbtGreen * gy[i][j];
            sum_bx += image[h + i - 1][w + j - 1].rgbtBlue * gx[i][j];
            sum_by += image[h + i - 1][w + j - 1].rgbtBlue * gy[i][j];
        }
    }

    // calculate the square root of the sum
    sum_r = round(sqrt(pow(sum_rx, 2) + pow(sum_ry, 2)));
    sum_g = round(sqrt(pow(sum_gx, 2) + pow(sum_gy, 2)));
    sum_b = round(sqrt(pow(sum_bx, 2) + pow(sum_by, 2)));

    // check for overflow
    if (sum_r > 255)
    {
        sum_r = 255;
    }
    if (sum_g > 255)
    {
        sum_g = 255;
    }
    if (sum_b > 255)
    {
        sum_b = 255;
    }

    RGBTRIPLE edge_pixel;
    edge_pixel.rgbtRed = sum_r;
    edge_pixel.rgbtGreen = sum_g;
    edge_pixel.rgbtBlue = sum_b;

    return edge_pixel;
}




// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //
    // 1.   Add a black pixel all around the image
    //      The image produced is 2 pixels wider
    //              and 2 pixels taller than the original
    //
    int border_height = height + 2;
    int border_width = width + 2;
    RGBTRIPLE border_image[border_height][border_width];

    RGBTRIPLE black_pixel;
    black_pixel.rgbtRed = 0;
    black_pixel.rgbtGreen = 0;
    black_pixel.rgbtBlue = 0;

    // scroll vertically
    for (int h = 0; h < border_height; h++)
    {
        // scroll horizontally
        for (int w = 0; w < border_width; w++)
        {
            // add a black pixel around the whole image
            // for the first and last columns and rows
            if ((h == 0) || (h == border_height - 1) || (w == 0) || (w == border_width - 1))
            {
                border_image[h][w] = black_pixel;
            }
            else
            {
                // copy the original image with a 1 pixel offset for the border
                border_image[h][w] = image[h - 1][w - 1];
            }
        }
    }

    //
    //  2.  Calculate the Edge detection with Sobel Operator
    //      The image produced is 2 pixels narrower
    //              and 2 pixels smaller than the original
    //
    RGBTRIPLE tmp_image[height][width];

    // Loop through the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the Sobel values and "ignoring" the black border
            tmp_image[i][j] = sobel_calc((i + 1), border_height, (j + 1), border_width, border_image);
        }
    }

    //
    //  3.  Copy the temporary image to the output
    //      The image produced the same size the original
    //
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = tmp_image[h][w];
        }
    }
    return;
}
