/**************************************
* week2, pset2 
* caesar.c
* 
* a program that encrypts messages using Vigenère’s cipher.
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
char cipher(char letter, char keyLetter);

int main(int argc, string argv[])
{
    // Chkek number of parameters
    if (argc != 2)
    {
        printf("launch program with one parameter like \" ./vigener traviata\"\n");
        return 1;
    }
    
    // Save input parameter as a key
    string key = argv[1];
    int keyLength = strlen(key);
    
    // Check if parameter is a word
    bool validKey = true;
    
    for(int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            validKey = false;
            break;
        }
    }
    if (!validKey)
    {
        printf("launch program with correct parameter like \" ./vigener traviata\"\n");
        return 1;
    }
    
    // Get user's string
    string userString = GetString();
    
    // Convert keyword into lower case
    for(int i = 0; i < keyLength; i++)
    {
        if (isupper(key[i]))
        {
            key[i] = tolower(key[i]);
        }
    }
    
    // Run through the line
    for(int i = 0, n = strlen(userString), j = 0; i < n; i++) // j is counter for key
    {
        userString[i] = cipher(userString[i], key[j % keyLength]);
        if (isalpha(userString[i]))
        {
            j++;
        }
    }
    
    // print result
    printf("%s\n", userString);
    
    return 0;
}

// encrypts symbol
char cipher(char letter, char keyLetter)
{
    if (isalpha(letter))
    {
        if (isupper(letter)) // encrypts uppercase
        {
            letter = (letter - 65 + keyLetter - 97) % 26 + 65;
        }else // encrypts lowercase
        {
            letter = (letter - 97 + keyLetter - 97) % 26 + 97;
        }
    }
    return letter;
}