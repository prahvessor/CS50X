/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP in scale determined by user.
 * 
 * Emin K. Aliiev
 * e-mail: emin.aliev@gmail.com
 * 
 *  /\
 * /  \
 *    /\
 *   /  \
 * 
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember scale
    int scale = atoi(argv[1]);
    
    if ((scale < 1) || (scale > 100))
    {
        printf("Parameter n must be a positive integer less than or equal to 100.\n");
        return 2;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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
    
    // save original biWidth and biHeight
    int originalWidth = bi.biWidth;
    //printf("width %i\n", bi.biWidth );
        
    // change width in biWidth field
    bi.biWidth *= scale;
    
    // change height in biHeigth field
    bi.biHeight *= scale;
    
    // determine paddings for scanlines
    int originalPadding = (4 - (originalWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // printf("new_width %i\n", bi.biWidth );
    // printf("origPadding %i\n", originalPadding);
    // printf("Padding %i\n", padding);

    // change size of image in bfSize biSizeImage
    // printf("old %i\n", bi.biSizeImage);    
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * 3 + padding);
    // printf("new %i\n", bi.biSizeImage);
    // change size of file in bfSize field
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;
    // printf("file size %i\n", bf.bfSize);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < (originalWidth); j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to scaled outfile
            for(int k = 0; k < scale; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
            }
        }

        // skip over padding, if any
        fseek(inptr, originalPadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
        
        // move pointer to the begining of the line 
        if ((i+1) % scale != 0)
        {
            fseek(inptr, -(originalWidth * 3 + originalPadding), SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
