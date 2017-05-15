/**************************************
* week2, pset2 
* initials.c
* 
* a program that prompts a user for their name 
* and then outputs their initials in uppercase with no spaces or periods
* 
* Emin K. Aliiev
* e-mail: emin.aliev@gmail.com
* 
*  /\
* /  \
*    /\
*   /  \
*
***************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // Get user's name
    string name = GetString();
    
    if (name != NULL)
    {
        // if printSymbol is true - print symbol, if false - don't print 
        bool printSymbol = true;
        
        // run througf the line
        for (int i = 0, n = strlen(name); i < n; i++)
        {
            if (isalpha(name[i]) && printSymbol)
            {
                printf("%c", toupper(name[i]));
                printSymbol = false;
            }else if (!isalpha(name[i]))
            {
                printSymbol = true;
            }
        }
        printf("\n");
    }
}
