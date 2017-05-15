/* Implementation of greedy algorithm
*/
#include <stdio.h>
#include <cs50.h>
#include <math.h>

float money = 0;
int rest = 0;

// calculation a number of coins
int getCoins(int balance, int rating)
{
    int coin = 0;
    while (rest >= rating)
    {
        coin = balance / rating;
        rest = balance % rating;
    }
    
    return coin;
}

// main function
int main(void)
{
    // input 
    do
    {
        printf("How much money: ");
        money = GetFloat();
    }
    while (money <= 0);
    
    // calculation a number of coins
    rest = roundf(money * 100);
    int sum = 0;
    int coins[] = {25,10,5,1};
    
    for(int i = 0; i < 4; i++)
    {
        sum += getCoins(rest, coins[i]);
    }

    // print result
    printf("%i\n", sum);
}