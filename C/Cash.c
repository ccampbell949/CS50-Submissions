//ask user for how much change
//print minimum number of coins required
//only coins are 25c, 10c, 5c and 1c
//include stdio.h
//include cs50.h
//include math.h
//use get float
//make sure it deals with negative values - do while

//divide the number by 25 first then 10, 5, 1


#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)  //main loop
{

    float change; //using float instead if int to accommodate decimals
    
    do  //repeating loop toensure positive value
    {
        change = get_float("Enter change in Dollars (Positve number): ");//prompt change in dollars format,i.e. not cents format
    }
    while (change <= 0);
        
        
    float coins;
    {
        change = round(change * 100);  //multiply by 100 to get cents value
        int numberofcoins = 0;
        
        while (change >= 25) //while change is greate rthan or equal to 25cents, divide by 25cent coin
        {
            change = change - 25;
            numberofcoins++;//add 1 to value of numberofcoins
        }
    
        while (change >= 10)//while change is greate rthan or equal to 10cents, divide by 10cent coin
        {
            change = change - 10;
            numberofcoins++;
        }
    
        while (change >= 5)//while change is greate rthan or equal to 5cents, divide by 5cent coin
        {
            change = change - 5;
            numberofcoins++;
        }
    
        while (change >= 1)//while change is greate rthan or equal to 1cent, divide by 1cent coin
        {
            change = change - 1;
            numberofcoins++;
        }
    
        printf("The Minimum number of coins is %i\n", numberofcoins);
    }
}
