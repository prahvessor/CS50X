/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// pointer to the root of trie
node* root;

// number of misspeled words
unsigned int words;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    
    int wordSize = strlen(word);
 
    // Points to root node
    node* pIterator = root;
 
    for (int i=0; i < wordSize; i++)
    {
        char c = tolower(word[i]);
 
        // Check for apostrophe
        if (c == '\'')
        {
            // 123 - (int)('a') = 123 - 97 = 26 (get index children[26] for apostroph)
            c = 123;
        }
 
        struct node* nextNode = pIterator->children[c - (int)('a')];
        if (nextNode != NULL)
        {
            pIterator = nextNode;
        }else
        {
            return false;
        }
    }
 
    if (pIterator->isWord == true)
    {
        return true;
    }
    return false;
    
    // return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    //return false;
    
    // Open dictionary file and check is exist
    FILE* speller = fopen(dictionary, "r");
    if (NULL == speller)
    {
        return false;
    }
    
    // Allocate mamory for root
    root = (node*)malloc(sizeof(node));
    
    // Point iterator to root of the trie
    node* pIterator = root;
    
    char c;
    while ((c = tolower(fgetc(speller))) != EOF)
    {
        
        if (c!='\n')
        {
            if (c == '\'')
            {
                // 123 - (int)('a') = 123 - 97 = 26 (get index children[26] for apostroph)
                c = 123;
            }
            struct node* nextNode = pIterator->children[c - (int)('a')];
            if (nextNode != NULL)
            {
                pIterator = nextNode;
            }else
            {
                pIterator->children[c - (int)('a')] = (node*)malloc(sizeof(node));
                pIterator = pIterator->children[c -(int)('a')];
            }
        }else
        {
            if (pIterator != root)
            {
                words++;
                pIterator->isWord = true;
 
                // set pointer to the root of the trie
                pIterator = root;                
            }
        }
    }
    
    fclose(speller);
    return true;
    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return words;
    // return 0;
}

/**
 * Recursion to free nodes
 */
void clear(node* pIterator)
{
    for (int i = 0; i < 27; i++)
    {
        if (pIterator->children[i] != NULL)
        {
            clear(pIterator->children[i]);
        }
    }
 
    free(pIterator);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    clear(root);
    return true;
    // return false;
}
