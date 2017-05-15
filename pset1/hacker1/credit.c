/* Bad Credit
*  
* a program that prompts the user for a credit card number and then reports whether it is a valid American Express, 
* MasterCard, or Visa card number, per the definitions of each’s format herein.
*
*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // read correct user's data
    long long userNumber = 0;
    do
    {
        printf("Input number of userNumber card: ");
        userNumber = GetLongLong();
    }
    while (userNumber <= 0);

    // convert number into array
    int cardNumberOriginal[20];
    int cardNumberCopy[20];
    long long rest = userNumber; 
    int count = 0; // number of symbols in userNumber card
    
    for(int i = 0; i < 20; i++)
    {
        if (rest <= 0 )
        {
            break;
        }
        cardNumberOriginal[i] = rest % 10;
        cardNumberCopy[i] = cardNumberOriginal[i];
        rest = rest / 10;
        count++;
    }

    // - implementation Luhn algorithm -
    
    // multiplication even members of array by 2
    for(int i = 1; i < count; i++)
    {
        cardNumberCopy[i] = cardNumberCopy[i] * 2;
        if (cardNumberCopy[i] > 9) 
        {
            int a = cardNumberCopy[i] / 10; // for example if cardNumber[i] == 18, then a == 1, 
            int b = cardNumberCopy[i] % 10; //                                          b == 8,
            cardNumberCopy[i] = a + b;      //           then cardNumber[i] == 1+8=9.
        }
        i++;
    }
    
    // total sum
    int sum = 0;
    for(int i = 0; i < count; i++)
    {
        sum += cardNumberCopy[i];
    }
    
    // determining control sum
    int controlSum = sum % 10;
    
    // --- end of Luhn algorithm----
    
    // determinign kind of card
    if (controlSum == 0)
    {
        if ((count == 15) && (cardNumberOriginal[count - 1] == 3) && 
            ((cardNumberOriginal[count - 2] == 4) || (cardNumberOriginal[count - 2] == 7)))
        {
            printf("AMEX\n");
        }
        else if (((count >= 13) && (count <= 16)) && (cardNumberOriginal[count - 1] == 4))
        {
            printf("VISA\n");
        }
        else if (((count >= 16) && (count <= 19)) && (cardNumberOriginal[count - 1] == 5) && 
            ((cardNumberOriginal[count - 2] >= 1) && (cardNumberOriginal[count - 2] <= 5)))
        {
            printf("MASTERCARD\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}