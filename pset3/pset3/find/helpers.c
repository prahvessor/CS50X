/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 * 
 * 
 * week3, pset3 
 * 
 * Emin K. Aliiev
 * e-mail: emin.aliev@gmail.com
 * 
 *  /\
 * /  \
 *    /\
 *   /  \
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int left = 0, right = n, mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (value < values[mid]) 
        {
            right = mid - 1;
            
        }else if (value > values[mid]) 
        {
            left = mid + 1;
            
        }else 
        {
            return true;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int basket = 0;
    // TODO: implement an O(n^2) sorting algorithm
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n - i; j++)
        {
            basket = values[j];
            if (basket > values[j + 1])
            {
                values[j] = values[j + 1];
                values[j + 1] = basket;
            }
        }
    }
    return;
}