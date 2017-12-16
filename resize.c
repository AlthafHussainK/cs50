/**
 * Resize a BMP piece by piece.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    float f = atof(argv[1]);

    //checking whether the number is valid or not
    if ( f < 0.00 && f > 100.0)
    {
        printf("Retry! Please enter a number between 0.00 and 100 \n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    int padding_old = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //new BITMAPINFOHEADER
    BITMAPINFOHEADER bi2 = bi;

    bi2.biWidth = bi.biWidth * f;
    bi2.biHeight = bi.biHeight * f;

    int padding_new = (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi2.biSizeImage = bi2.biWidth*abs(bi2.biHeight)*3 + padding_new*abs(bi2.biHeight);

    //new BITMAPFILEHEADER
    BITMAPFILEHEADER bf2 = bf;

    bf2.bfSize = bi2.biWidth*abs(bi2.biHeight)*3 + padding_new*abs(bi2.biHeight) + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);
    //compress image
    if (f < 1.0)
    {
        // iterate over infile's scanlines
        for (int i = 0; i < abs(bi2.biHeight); i++ )
        {

            // iterate over pixels in scanline
            for (int j = 0; j < bi2.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                //no. of pixels to skip over
                fseek(inptr, (1/f-1)*sizeof(RGBTRIPLE), SEEK_CUR);

            }
            // padding to the new image
            for (int k = 0; k < padding_new; k++)
            {
                fputc(0x00, outptr);
            }

            // skip the remaining padding
            fseek(inptr, (padding_old + (bi.biWidth * 3) + padding_old), SEEK_CUR);
        }
    }

    // enlarge the image
    else
    {
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            for (int px = 0; px < f; px++)
            {
                for (int m = 0; m < bi.biWidth ; m++)
                {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int n = 0; n < f; n++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                }
                //for loop to fwrite new padding
                for (int l = 0; l < padding_new; l++)
                {
                    fputc(0x00, outptr);
                }
                //if px is at last verticle resize
                if (px < f-1)
                {
                   fseek(inptr, -1 * (bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
                }
            }
            // skip over padding, if any
            fseek(inptr, padding_old, SEEK_CUR);
        }
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
