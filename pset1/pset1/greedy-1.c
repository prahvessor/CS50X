/* Implementation of greedy algorithm
*/
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // input 
    float money = 0;
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
    int rest = roundf(money * 100);
    int sum = 0;
    
    // calculation a number of quarters
    while (rest >= 25)
    {
        rest = rest - 25;
        quarter++;
    }
    
    // calculation a number of dimes
    while (rest >= 10)
    {
        rest = rest - 10;
        dimes++;
    }
    
    // calculation a number of nickels
    while (rest >= 5)
    {
        rest = rest - 5;
        nickels++;
    }
    
    // calculation a number of pennies
    while (rest >= 1)
    {
        rest = rest - 1;
        pennies++;
    }
    
    // calculation a sum of coins
    sum = quarter + dimes + nickels + pennies;
    
    // print result
    printf("%i\n", sum);
    
    
}