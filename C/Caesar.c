//ask use for inout word and key
//key determines how many steps forward the letters go
// single line argument
//non-negative number
//must print error message
//numbers must not be a decimal
//must output plain text
// must output cupher text
//must preserve captials and lower case
//new line
//return 0

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) //command line inputs
{
    
    if (argc <= 1 || argc > 2) //if argument count is less than 1 or more than 2, return error
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }


    for (int i = 0; argv[1][i] != '\0';
         i++)// loop through each of the character position (i) in the argument in position '1' on command line 
    {
        if (isalpha(argv[1][i]) != 0) //if one of the characters is an alphabetical character, return error and stop programme
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
        
    int k = atoi(
                argv[1]); //use function atoi to convert the 'string' of numberic characters in argv1 into an integer  of these values. i.e. string of "20" becomes 20
    //style50 telling me I need to take a new line and split the atoi function here...why?
    string plaintext = get_string("Text to be encrypted: "); //User input of text to be converted
    
    printf("Ciphertext: ");
    int i = strlen(plaintext); //length of the string entered by user
    for (int x = 0; x < i; x++) //itereate over each character for the length of the string entered by user
    {
        if (isupper(plaintext[x])) //if the letter is uppercase, use the following formula
        {
            printf("%c", (((plaintext[x] - 65) + k) % 26) +
                   65);  //convert character from it's ASCII value to an assigned '0', '1', '2', then add the key value to the position. Convert this final position back into ASCII format
        }
        else if (islower(plaintext[x]))  
        {
            printf("%c", (((plaintext[x] - 97) + k) % 26) + 
                   97);  //convert character from it's ASCII value to an assigned '0', '1', '2', then add the key value to the position. Convert this final position back into ASCII format. 
            //note here that the lower-case ASCII values are used
        }
        else       
        {
            printf("%c", 
                   plaintext[x]); //this code allows for any characters that are not upper or lower case to be re-printed as-is. i.e. exclamation point, space etc. 
        }

    }
    printf("\n"); //prints new line. tried to do this in line aboce, but caused output errors.
}

//Absolutely no clue whats going on with the formatting that style50 is making me do...oh well.If new lines is what it wants, new lines is what it'll get

