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
    int quarter = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    rest = roundf(money * 100);
    int sum = 0;
    
    // calculation a number of each coins
    quarter = getCoins(rest, 25);
    dimes = getCoins(rest, 10);
    nickels = getCoins(rest, 5);
    pennies = getCoins(rest, 1);
    
    // calculation a sum of coins
    sum = quarter + dimes + nickels + pennies;

    // print result
    printf("%i\n", sum);
}