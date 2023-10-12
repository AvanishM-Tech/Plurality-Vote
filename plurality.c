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
    // rotate through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //check if user entered input matches entered candidates name
        if (strcmp(name, candidates[i].name) == 0)
        {
            //increases candidate vote count by one if the above conditions are satisfied
            candidates[i].votes++;
            return true;
        }
    }
    return false;

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //initializes a variable hv which stands for highest vote
    int hv = 0;
    int n = 0;
    //initializes an array for storing the highest values along with name
    candidate highest[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        //checks if votes of each candidate is greater than the hv
        if (candidates[i].votes > hv)
        {
            //updates hv if so
            hv = candidates[i].votes;
            highest[n].votes = hv;
            highest[n].name = candidates[i].name;
        }
        //for ties
        else if (candidates[i].votes == highest[n].votes)
        {
            n++;
            highest[n].votes = candidates[i].votes;
            highest[n].name = candidates[i].name;
        }
    }
    for (int i = 0; i < n + 1; i++)
    {
        printf("%s\n", highest[i].name);
    }
    return;
}
