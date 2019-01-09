// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *m = argv[1];
    int n = atoi(m);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
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
        return 4;
    }

    //save data from the input file
    LONG biWidth_old = bi.biWidth;
    LONG biHeight_old = bi.biHeight;
    int padding_old = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //determine biWidth, biHeight, padding and biSizeImage for the output file
    bi.biWidth *= n;
    bi.biHeight *= n;
    int padding_new = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding_new) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(biHeight_old); i < biHeight; i++)
    {
        //make sure to vertically scale the infile
        for (int p = 0; p < n; p++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < biWidth_old; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n number of times (horizontally scale the infile)
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }
            //The cursor now is at the end of the line. Add padding to the outptr
            for (int k = 0; k < padding_new; k++)
            {
                fputc(0x00, outptr);
            }

            //send infile cursor back to the beginning of a scanline
            fseek(inptr, -abs(biWidth_old) * sizeof(RGBTRIPLE), SEEK_CUR);
        }

        // The cursor now is in the beginning of the line. Skip over all RGBtriples and padding, if any
        fseek(inptr, padding_old + abs(biWidth_old) * sizeof(RGBTRIPLE), SEEK_CUR);


    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
