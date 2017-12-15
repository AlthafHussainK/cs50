/**
 * Copies a BMP piece by piece, just because.
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

    int f = atoi(argv[1]);

    //edit needed==============================================
    if ( f < 1 && f > 100)
    {
        printf("Retry \n");
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

    BITMAPINFOHEADER bi2 = bi;

    int padding_old = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("%d\n", padding_old);


    bi2.biWidth = bi.biWidth * f;

    bi2.biHeight = bi.biHeight * f;


    int padding_new = (4 - (bi.biWidth * sizeof(RGBTRIPLE) * f) % 4) % 4;

    printf("%d\n", padding_new);

    bi2.biSizeImage = bi.biWidth*abs(bi.biHeight)*f*f*3 + padding_new*abs(bi.biHeight)*f;

    BITMAPFILEHEADER bf2 = bf;

    bf2.bfSize = bi.biWidth*abs(bi.biHeight)*f*f*3 + padding_new*abs(bi.biHeight)*f + 54;

    int size = bf2.bfSize;
    int w = bi.biWidth;
    int h = bi.biHeight;
    int imgsize = bi2.biSizeImage;
    printf("%d  %d\n %d %d\n", size, imgsize, w, h);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int vcount = 0; vcount < f; vcount++)
        {
            for (int m = 0; m < bi.biWidth ; m++)
            {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // iterate over pixels in scanline
            for (int hcount = 0; hcount < f; hcount++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            }
            //for loop to fwrite new padding
            for (int l = 0; l < padding_new; l++)
            {
                fputc(0x00, outptr);

            }

        if (vcount < (f-1))
               {
               fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
               }
        }
    fseek(inptr, padding_old, SEEK_CUR);
    }



    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
