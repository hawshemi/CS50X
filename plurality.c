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
    // Loop through the Candidate count
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate is equal to what is user's input
        if (strcmp(candidates[i].name, name) == 0)
        {
            // If equal to user input, increase the specific candidate vote
            candidates[i].votes++;
            return true;
        }
    }
    // Else if not equal to candidate vote return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_vote = 0;

    // Iterate over list of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check for candidate votes that are greater than max_vote and set them to max_vote
        if (candidates[i].votes > max_vote)
        {
            max_vote = candidates[i].votes;
        }
    }

    // Iterate over list of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Check for candidate votes that are equal to max_vote and print them
        if (candidates[i].votes == max_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}