//prompt for string of text get_string
//count number of letters and words
//any sequence of letters seperated by spaces should count as a word
// any indication of ., ! or ? denites the end of a sentence
//output should be Grade x
//over 16 = 16+
//under 1 = before grade 1

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{

    string text = get_string("Text: "); //Get text input from user

//Set initial parameters
    float letters = 0;
    float words = 1;
    float sentences = 0;
    int i = strlen(text);
    
    for (int x = 0; x < i; x++) //loop to count 
    {
        if (isalpha(text[x])) //if character at location 'x' in t 'text' is a letter, add 1 to 'Letters'
        {
            letters++;
        }
        if (isspace(text[x])) //if character at location 'x' is a space, this indicates a new word, so add 1 to 'words'
        {
            words++;
        }
        if (text[x] == '!' || text[x] == '?'
            || text[x] == '.') // if text equals ! OR ? OR ., this indicates the end of a sentence, so add 1 to 'sentences'
        {
            sentences++;
        }
    }

    float L = letters / words * 100;// L is the number of letters per 100 words
    float S = sentences / words * 100; // S is the number of sentences per 100 words.
    float indexFloat = 0.0588 * L - 0.296 * S - 15.8;
    int indexInteger = round(indexFloat); // round the float value of indexFloat

    if (indexInteger >= 1 && indexInteger <= 16) //between 1 and 16, display grade number
    {
        printf("Grade %i\n", indexInteger);
    }
    else
    {
        if (indexInteger < 1) //if grade is less than 1:
        {
            printf("Reading Grade: Before Grade 1\n");
        }
        if (indexInteger > 16) // id grade is over 16:
        {
            printf("Reading Grade: Grade 16+\n");
        }
    }
}
