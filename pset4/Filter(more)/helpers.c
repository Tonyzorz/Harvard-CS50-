#include "helpers.h"
#include <math.h>
#include <stdio.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    RGBTRIPLE gx[1][1];
    RGBTRIPLE gy[1][1];
    RGBTRIPLE value[1][1];

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            // = -1*(0) + 0*(0) + 1*(0) + -2*(0) + 0*(0) + 2*(0) + -1*(0) + 0*(0) + 1*(0);
            // = -1*(0) + -2*(0) + -1*(0) + 0*(0)+ 0*(0)+ 0*(0) + 1*(0) + 2*(0) + 1*(0);
            //left upper corner
            if(i == 0 && j == 0){

                gx[0][0].rgbtBlue = 0*(image[i][j].rgbtBlue) + 2*(image[i][j + 1].rgbtBlue) + 0*(image[i + 1][j].rgbtBlue) + 1*(image[i + 1][j + 1].rgbtBlue);
                printf("%i\n", gx[0][0].rgbtBlue);
                gy[0][0].rgbtBlue = 0*(image[i][j].rgbtBlue) + 0*(image[i][j + 1].rgbtBlue) + 2*(image[i + 1][j].rgbtBlue) + 1*(image[i + 1][j + 1].rgbtBlue);
                printf("%i\n", gy[0][0].rgbtBlue);
                value[0][0].rgbtBlue = ((sqrt(gx[0][0].rgbtBlue^2 + gy[0][0].rgbtBlue^2)) > 255) ? 255 : round((gx[0][0].rgbtBlue^2 + gy[0][0].rgbtBlue^2));
                printf("%i\n", value[0][0].rgbtBlue);
                gx[0][0].rgbtRed = 0*(image[i][j].rgbtRed) + 2*(image[i][j + 1].rgbtRed) + 0*(image[i + 1][j].rgbtRed) + 1*(image[i + 1][j + 1].rgbtRed);
                gy[0][0].rgbtRed = 0*(image[i][j].rgbtRed) + 0*(image[i][j + 1].rgbtRed) + 2*(image[i + 1][j].rgbtRed) + 1*(image[i + 1][j + 1].rgbtRed);
                value[0][0].rgbtRed = (round((gx[0][0].rgbtRed^2 + gy[0][0].rgbtRed^2)) > 255) ? 255 : round((gx[0][0].rgbtRed^2 + gy[0][0].rgbtRed^2));

                gx[0][0].rgbtGreen = 0*(image[i][j].rgbtGreen) + 2*(image[i][j + 1].rgbtGreen) + 0*(image[i + 1][j].rgbtGreen) + 1*(image[i + 1][j + 1].rgbtGreen);
                gy[0][0].rgbtGreen = 0*(image[i][j].rgbtGreen) + 0*(image[i][j + 1].rgbtGreen) + 2*(image[i + 1][j].rgbtGreen) + 1*(image[i + 1][j + 1].rgbtGreen);
                value[0][0].rgbtGreen = (round((gx[0][0].rgbtGreen^2 + gy[0][0].rgbtGreen^2)) > 255) ? 255 : round((gx[0][0].rgbtGreen^2 + gy[0][0].rgbtGreen^2));

                temp[i][j].rgbtBlue = value[0][0].rgbtBlue;
                temp[i][j].rgbtRed = value[0][0].rgbtRed;
                temp[i][j].rgbtGreen = value[0][0].rgbtGreen;
            //right upper corner
            } else if(i == 0 && j == width - 1){
                gx[0][0].rgbtBlue = 0*(image[i + 1][j].rgbtBlue) + -2*(image[i][j - 1].rgbtBlue) + -1*(image[i + 1][j - 1].rgbtBlue);
                gy[0][0].rgbtBlue = 2*(image[i + 1][j].rgbtBlue) + 0*(image[i][j - 1].rgbtBlue) + 1*(image[i + 1][j - 1].rgbtBlue);
                value[0][0].rgbtBlue = (gx[0][0].rgbtBlue^2 + gy[0][0].rgbtBlue^2 > 255) ? 255 : round(gx[0][0].rgbtBlue^2 + gy[0][0].rgbtBlue^2);

                gx[0][0].rgbtRed = 2*(image[i][j - 1].rgbtRed) + 0*(image[i + 1][j].rgbtRed) + 1*(image[i + 1][j - 1].rgbtRed);
                gy[0][0].rgbtRed = 0*(image[i][j - 1].rgbtRed) + 2*(image[i + 1][j].rgbtRed) + 1*(image[i + 1][j - 1].rgbtRed);
                value[0][0].rgbtRed = (gx[0][0].rgbtRed^2 + gy[0][0].rgbtRed^2 > 255) ? 255 : round(gx[0][0].rgbtRed^2 + gy[0][0].rgbtRed^2);

                gx[0][0].rgbtGreen = 2*(image[i][j - 1].rgbtGreen) + 0*(image[i + 1][j].rgbtGreen) + 1*(image[i + 1][j - 1].rgbtGreen);
                gy[0][0].rgbtGreen = 0*(image[i][j - 1].rgbtGreen) + 2*(image[i + 1][j].rgbtGreen) + 1*(image[i + 1][j - 1].rgbtGreen);
                value[0][0].rgbtGreen = (gx[0][0].rgbtGreen^2 + gy[0][0].rgbtGreen^2 > 255) ? 255 : round(gx[0][0].rgbtGreen^2 + gy[0][0].rgbtGreen^2);

                temp[i][j].rgbtBlue = value[0][0].rgbtBlue;
                temp[i][j].rgbtRed = value[0][0].rgbtRed;
                temp[i][j].rgbtGreen = value[0][0].rgbtGreen;
            //left bottom corner
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
