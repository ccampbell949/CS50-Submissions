#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100 //define max values for these 2 variables
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate; // layout of variable "candidate"

// Array of candidates
candidate candidates[MAX_CANDIDATES]; // size of array is equal to max candidates

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1; //-1 as indexing starts at 0
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; //populating matrix "candidates"
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS) //display error if voter count is greater than defined max voters
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++) //loop
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)// loop
        {
            string name = get_string("Rank %i: ", j + 1); //user input for each rank

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name); // print all names
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int a = 0; a < candidate_count; a++) //loop
    {
        if (strcmp(name, candidates[a].name) == 0)  //if string values equal:
        {
            preferences[voter][rank] = a;  
            //assign array value of candidate position to 2 dimensional array position for a specific voter e.g. voter 1's 1st ranked candidate
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++)
    {
        for (int a = 0; a < candidate_count; a++) //loop
        {
            int b = preferences[i][a]; //this value, 0 thu max voters, is checked against the array of candidates e.g. 0 - first candidate, 1 - second etc
            if (candidates[b].eliminated == false) // checks particular candidate at that array position's "eliminated" status
            {
                candidates[b].votes++; // if not eliminated, increment vote by 1
                break;
            }
        }
    }
}



// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int a = 0; a < candidate_count; a++) //loop
    {
        if (candidates[a].votes > (voter_count / 2)) //if candidtae has majority vote, they win at this stage. Majority > max voters/2
        {
            printf("%s\n", candidates[a].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int voteCount = voter_count;
    for (int a = 0; a < candidate_count; a++) //loop
    {
        if (candidates[a].votes < voteCount && candidates[a].eliminated == false) 
            //if a candidates votes are less than the than the total votecount, and hasn't been eliminated,
        {
            voteCount = candidates[a].votes; //the votecount is now equal to that particular candidates vote count
        }
    }
    return voteCount;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int tiedVotes = 0;
    int running = 0;

    for (int a = 0; a < candidate_count; a++) //loop
    {
        //if candidate is not eliminatedand candidate votes are minimum, incrememnt both variables
        if (candidates[a].eliminated == false && candidates[a].votes == min)
        {
            tiedVotes++;
            running++;
        }
        else if (candidates[a].eliminated == false) //if not min, only increment running
        {
            running++;
        }
    }
    if (tiedVotes == running) //if all running candidates are tied, return tied
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int a = 0; a < candidate_count; a++) //loop
    {
        //if candidate has min votes and is not currently eliminated:
        if (candidates[a].eliminated == false && candidates[a].votes == min)
        {
            candidates[a].eliminated = true; // eliminate that candidate
        }
    }
}

