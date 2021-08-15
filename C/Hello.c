#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name?\n"); /*Ask user for their name*/
    printf("Hello, %s\n", name); /*Print "Hello " + the users name*/
}
