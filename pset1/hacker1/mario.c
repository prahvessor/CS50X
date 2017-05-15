/******************************************************************* 
*
* Building Mario's pyramid 
* depending on user's input number of steirs
*
*     /\  ©
*    /  \
*       /\
*      /  \
*
*******************************************************************/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // input number of stairs (between 0 and 23)
    int height = 0;
    do
    {
        printf("Input heigth of pyramid between 0 and 23: ");
        height = GetInt();
    }
    while ((height < 0) || (height > 23));
    
    // drawing pyramid
    for(int i = 0; i < height; i++)
    {
        // drawing spaces
        for(int k = height; k > i + 1; k--)
        {
            printf(" ");
        }
        
        // drawing hashes
        for(int j = 0; j <= i; j++) 
        {
            printf("#");
        }
        
        // drawing spaces
        printf("  ");
        
        // drawing hashes
        for(int j = 0; j <= i; j++) 
        {
            printf("#");
        }
        
        printf("\n");
    }
}