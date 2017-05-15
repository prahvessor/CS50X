/* counting water bottles
*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get amount of minutes from user
    int minutes = 0;
    do
    {
        printf("minutes: ");
        minutes = GetInt();
    }
    while (minutes <= 0);
    
    
    //Output equivalent in bottles
    printf("bottles: %i\n", minutes * 12);
}