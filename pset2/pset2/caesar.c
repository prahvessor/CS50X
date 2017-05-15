/**************************************
* week2, pset2 
* caesar.c
* 
* a program that encrypts messages using Caesar’s cipher.
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
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//prototype
char cipher(char letter, int key);

int main(int argc, string argv[])
{
    // Check number of parameters and if parameter is positive
    if ((argc != 2) || (atoi(argv[1]) < 1))
    {
        printf("launch program with needed parameter like \" ./ceasar 12\"\n");
        return 1;
    }
    
    // Save key
    int key = atoi(argv[1]);
    
    // Get user's string
    string userString = GetString();
    
    // Run through the line
    for(int i = 0, n = strlen(userString); i < n; i++)
    {
        userString[i] = cipher(userString[i], key);
    }
    
    // print
    printf("%s\n", userString);
    
    return 0;
}

// encrypts symbol
char cipher(char letter, int key)
{
    if (isalpha(letter))
    {
        if (isupper(letter)) // encrypts uppercase
        {
            letter = (letter - 65 + key) % 26 + 65;
        }else  // encrypts lowercase
        {
            letter = (letter - 97 + key) % 26 + 97;
        }
    }
    return letter;
}