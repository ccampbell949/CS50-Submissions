#include <cs50.h>
#include <stdio.h>

int main(void)
{
   
    printf("What is the starting population size?\n"); /*Ask user for initial population size*/
    int n;
    do
    {
        n = get_int("Positive Integer: "); /*Prompt for a positive integer*/
    }
    while (n < 9); /*Continually re-asks if input is under 9*/

    printf("What is the end population?\n");/*Asks for end population size*/
    int end;
    do
    {
        end = get_int("Positive Integer. Greater than Starting size: ");
    }
    while (end < n); /*Continually re-asks if end pop. size less than start pop.*/
    

    int calc;
    
    int years = 0;
    
    if (end > n) /*If end pop size more than start, run calc.*/
    {
        do
        {
            n = n + (n / 3) - (n / 4);
            years++;
        }
        
        while (n < end);
    }
    else;
    printf("Years: 0"); /* if start and end, display "Years: 0"*/
    
    printf("Years: %i", years); /*Print the number od years required to reach end population size from start*/

 
}
