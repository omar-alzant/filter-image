#include "helpers.h"
#include <math.h>
#include <ctype.h>
#include <stdlib.h>



// (int)round(index)

// images [0][1].rgbtRed = red val;  --> set the pixel [0][1]'Red  to red val;



// Convert image to grayscale

//In fact, to ensure each pixel of the new image still has
//the same general brightness or darkness as the old image,
//we can take the average of the red, green,
//and blue values to determine what shade of grey to make the new pixel.


void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            float avr = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0 ;
            int avri = round(avr);

            if (avri == 255 || avri == 0)
            {
                if (avri == 255)
                {
                    image[i][j].rgbtRed = image[i][j].rgbtBlue = image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtRed = image[i][j].rgbtBlue = image[i][j].rgbtGreen = 0;
                }
            }
            else
            {
                image[i][j].rgbtRed = image[i][j].rgbtBlue = image[i][j].rgbtGreen = avri;
            }
        }
    }

    return;
}





// Convert image to sepia

//sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
//sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue
//sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue


void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {

            double sepiaRed =    0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            double sepiaGreen =  0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            double sepiaBlue =   0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;


            int sR = round(sepiaRed);
            int sG = round(sepiaGreen);
            int sB = round(sepiaBlue);

            if ((sR >= 0 && sR <= 255))
            {
                image[i][j].rgbtRed = sR ;
            }
            else
            {
                if (sR > 255)
                {
                    image[i][j].rgbtRed = 255 ;
                }
            }
            if ((sG >= 0 && sG <= 255))
            {
                image[i][j].rgbtGreen = sG ;
            }
            else
            {
                if (sG > 255)
                {
                    image[i][j].rgbtGreen = 255 ;
                }
            }

            if ((sB >= 0 && sB <= 255))
            {
                image[i][j].rgbtBlue = sB ;
            }
            else
            {
                if (sB > 255) 
                {
                    image[i][j].rgbtBlue = 255 ;
                }


            }       

        }
    }

    return;
}



// Reflect image horizontally



void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE a[height][width];

    for (int i = 0 ; i < height  ; i++)
    {
        for (int j = 0 ; j < width / 2 ; j++)
        {
            a[i][j] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = a[i][j];
        }

    }
    return;
}





// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    
    
    //create a temporary image to be blurred
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }   
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumB;
            int sumG;
            int sumR;
            float counter; 
            
            sumB = sumG = sumR = counter = 0;     
            
            
            if (i >= 0 && j >= 0)
            {
                sumR += temp[i][j].rgbtRed;
                sumG += temp[i][j].rgbtGreen;
                sumB += temp[i][j].rgbtBlue;
                counter++;
            }

            if (i >= 0 && j - 1 >= 0)
            {
                sumR += temp[i][j - 1].rgbtRed;
                sumG += temp[i][j - 1].rgbtGreen;
                sumB += temp[i][j - 1].rgbtBlue;
                counter++;
            }
            if (i - 1 >= 0 && j >= 0)
            {
                sumR += temp[i - 1][j].rgbtRed;
                sumG += temp[i - 1][j].rgbtGreen;
                sumB += temp[i - 1][j].rgbtBlue;
                counter++;
            }
            //corner pixel on top right
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                sumR += temp[i - 1][j - 1].rgbtRed;
                sumG += temp[i - 1][j - 1].rgbtGreen;
                sumB += temp[i - 1][j - 1].rgbtBlue;
                counter++;
            }//FOUR EDGES            //pixels on bottom edge
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                sumR += temp[i][j + 1].rgbtRed;
                sumG += temp[i][j + 1].rgbtGreen;
                sumB += temp[i][j + 1].rgbtBlue;
                counter++;
            }            
            
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                sumR += temp[i - 1][j + 1].rgbtRed;
                sumG += temp[i - 1][j + 1].rgbtGreen;
                sumB += temp[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                sumR += temp[i + 1][j].rgbtRed;
                sumG += temp[i + 1][j].rgbtGreen;
                sumB += temp[i + 1][j].rgbtBlue;
                counter++;
            }
        
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                sumR += temp[i + 1][j - 1].rgbtRed;
                sumG += temp[i + 1][j - 1].rgbtGreen;
                sumB += temp[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            
            
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                sumR += temp[i + 1][j + 1].rgbtRed;
                sumG += temp[i + 1][j + 1].rgbtGreen;
                sumB += temp[i + 1][j + 1].rgbtBlue;
                counter++;
            }
            
            image[i][j].rgbtRed = round(sumR / counter);
            image[i][j].rgbtGreen = round(sumG / counter);
            image[i][j].rgbtBlue = round(sumB / counter);
        }
    }
    return;
}