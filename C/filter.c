#include "helpers.h"
#include <stdio.h>
#include <cs50.h>
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //need to loop through each pixel in rows and columns
    for (int i = 0; i < height; i++)//loop through rows
    {
        for (int j = 0; j < width; j++)
        {
            //get values of red, green and blue and calculate the average
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            
            //Calculate the average of these values as a  integer
            int averageValue = round((red + green + blue) / 3);
            
            //Make each colour value equal to the average value
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = averageValue;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)//same loops as above for column and rows
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed; //obtain colour values at eachpixel location
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            
            //calculate new Sepia values using formulas provided
            //values as integers
            int redSepia = round(0.393 * red + 0.769 * green + 0.189 * blue);
            
            //make sure value is below 255, as this is max value. If not, manually make value 255
            
            if (redSepia > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = redSepia;
            }
            
            int greenSepia = round(0.349 * red + 0.686 * green + 0.168 * blue);
            
            //again, make sure value is not above 255:
            if (greenSepia > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = greenSepia;
            }
            
            int blueSepia = round(0.272 * red + 0.534 * green + 0.131 * blue);
            
            //ensure value is set to 255 max if value is greater than 255
            
            if (blueSepia > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blueSepia;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)//same loop as above to loop through pixels
    {
        for (int j = 0; j < width / 2; j++)//need to loop over half the width becuse we are swapping. 
            //therefore, you only do n/2 swaps e.g. swapping 10 things in pairs requires 5 steps/swaps
        {
            RGBTRIPLE temp = image[i][j]; //create temporary variable i.e empty glass
            image[i][j] = image[i][width - (j + 1)];//moving along columns, swapping pairs
            image[i][width - (j + 1)] = temp;//write the temp value into new pixel location on opposite side
            //note that we are reflecting on the vertical axis
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    
    for (int i = 0; i < height; i++) //loop through the pixels
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed, sumGreen, sumBlue; //variables to work out sum of middle and surrounding pixels
            sumRed = sumGreen = sumBlue = 0; //set equal to zero
            float counter = 0;
            
            for (int a = -1; a < 2; a++) //iterate through each neighbouring pixel, including central
            {
                for (int b = -1; b < 2; b++)
                {
                    int currenta = i + a;
                    int currentb = j + b;
                    
                    if (currenta < 0 || currenta > (height - 1) || currentb < 0 || currentb > (width - 1)) //check for edges of 3x3 square
                    {
                        continue;
                    }
                    
                    sumRed += image[currenta][currentb].rgbtRed; //add and assign to sumRed, sumGreen, sumBlue
                    sumGreen += image[currenta][currentb].rgbtGreen;
                    sumBlue += image[currenta][currentb].rgbtBlue;
                    
                    counter++;
                }
                
                temp[i][j].rgbtRed = round(sumRed / counter); //iterate over pixels and assign rounded average of Red, green and blue to the sums
                temp[i][j].rgbtGreen = round(sumGreen / counter);
                temp[i][j].rgbtBlue = round(sumBlue / counter);
            }
        }
        
    }
    
    for (int i = 0; i < height; i++) //iterate over each pixel in the array
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed; //replace original pixels with those held in temporary
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
        
    }
    return;
}
   

