#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Must check that name entered matches names given as arguments in the command line
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 
            0) // use strcomp (string compare) to compare entered name on vote to command line arguments (names on ballot)
        { 
            // ^not sure why style50 wanted a new line here for the 0...
        
            //if names match, increment candidate vote by 1
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //Determine the maximum nuber of votes
    int maximumvotes = 0;//set variable "maximumvote" equal to 0
    for (int i = 0; i < candidate_count; i++)//iterate over each candidate
    {
        if (candidates[i].votes > maximumvotes)//if votes for candidate in indexi is greater than maximumvotes, 
        {
            maximumvotes = candidates[i].votes;//set this as new maximumvotes value
        }
    }
    
    //Print names of winning candidates
    for (int i = 0; i < candidate_count; i++)//iterate over each candidate name
    {
        if (candidates[i].votes == maximumvotes) //if candidate in indexi's vote is equal to the maximum vote in the array,
        {
            printf("%s\n", candidates[i].name); //print their name (/5splaceholder for string "candidates[i].name")
        }
    }
    return;
    
}
