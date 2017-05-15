/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
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
#include <stdint.h>

typedef uint8_t  BYTE;

int main(void)
{
    // TODO
    
    // file counter
    int fileCounter = 0;
    
    FILE* inptr = fopen("card.raw", "r");
    
    // check for existing card.raw file
    if (inptr == NULL)
    {
        printf("Could not open \"card.raw\".\n");
        return 1;
    }

    // buffer
    BYTE buffer[512];
    
    // file name
    char fileName[8];
    
    //
    FILE* outptr = NULL;
    
    // repeat until end of card
    while(fread(buffer, sizeof(buffer), 1, inptr) > 0)
    {
        
        // start new jpg?
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] == 0xe0) || (buffer[3] == 0xe1)))
        {
            // if new jpg found, should close previous
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            
            //create name for new jpg
            sprintf(fileName,"%.3d.jpg", fileCounter);
            
            // create new file
            outptr = fopen(fileName, "w");
            
            // write first 512 bytes to file
            fwrite(buffer, sizeof(buffer), 1, outptr);
            
            fileCounter++;
        }else if (fileCounter > 0)
        {
            // append buffer to existing file
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
        
    }

    fclose(outptr);    
    
    // close the file
    fclose(inptr);

    // that's all folks
    return 0;
    
}
