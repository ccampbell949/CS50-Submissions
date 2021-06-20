#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;

    do
    {
        n = get_int("Enter Height: ");/*ask user for height*/

    }
    while (n < 1 || n > 8);/*input must be between 1 and 8 inclusive*/


    for (int i = n - 1; i >= 0 ; i--)/*for loop to each line*/
    {
        for (int j = 0; j < i; j++)/*as long as jisless than i execute*/
        {
            printf(" ");
        }

        for (int a = i; a < n ; a++) /* aslong as a is less than n, execute and add 1 to a*/
        {
            printf("#");
        }

        printf("\n");
    }
}
