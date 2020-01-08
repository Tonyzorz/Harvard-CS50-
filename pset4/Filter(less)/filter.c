#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            float avg = round((float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if(sepiaRed > 255) sepiaRed = 255;
            if(sepiaGreen > 255) sepiaGreen = 255;
            if(sepiaBlue > 255) sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0, n = width/2; j < n; j++){
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            //left upper corner
            if(i == 0 && j == 0){
                temp[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue)/4);
                temp[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen)/4);
                temp[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed)/4);
            //right upper corner
            } else if(i == 0 && j == width - 1){
                temp[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue)/4);
                temp[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen)/4);
                temp[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed)/4);
            //left bottom corner
            } else if(i + 1 == height && j == 0){
                temp[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue)/4);
                temp[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen)/4);
                temp[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed)/4);
            //right bottom corner
            } else if(i + 1 == height && j + 1 == width){
                temp[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue)/4);
                temp[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen)/4);
                temp[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed)/4);
            //check for up
            } else if(i == 0){
                temp[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue)/6);
                temp[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen)/6);
                temp[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed)/6);
            //check for left
            } else if(j == 0){
                temp[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue)/6);
                temp[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen)/6);
                temp[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed)/6);
            //chekc for right
            } else if(j == width - 1){
                temp[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue)/6);
                temp[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen)/6);
                temp[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed)/6);
            //check for bottom
            } else if(i == height - 1){
                temp[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue)/6);
                temp[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen)/6);
                temp[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed)/6);
            //add all
            } else {
                temp[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue)/9);
                temp[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen)/9);
                temp[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed +
                image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed)/9);
            }

        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            image[i][j] = temp[i][j];
        }
    }
    return;
}
