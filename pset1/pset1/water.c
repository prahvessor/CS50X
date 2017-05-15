/* counting water bottles
*/
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get amount of minutes from user
    printf("minutes: ");
    int minutes = GetInt();
    
    //Output equivalent in bottles
    printf("bottles: %i\n", minutes * 12);
}