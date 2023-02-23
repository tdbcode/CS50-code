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
        else
        {
            printf("Vote registered.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int c = 0; c < candidate_count; c++)
    {
        if (strcmp(name, candidates[c].name) == 0)
        {
            candidates[c].votes += 1;
            return true;
            break;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{

    bool flag = true;
    candidate winner;
    candidate second;
    string tempName = NULL;
    int tempVotes = 0;

    while (flag)
    {
        flag = false;
        for (int c = 0; c < candidate_count; c++)
        {
            if (candidates[c].votes < candidates[c + 1].votes)
            {
                tempName = candidates[c + 1].name;
                tempVotes = candidates[c + 1].votes;
                candidates[c + 1].name = candidates[c].name;
                candidates[c + 1].votes = candidates[c].votes;
                candidates[c].name = tempName;
                candidates[c].votes = tempVotes;
                flag = true;
            }
        }
    }

    winner = candidates[0];
    second = candidates[1];

    if (winner.votes == second.votes)
    {
        printf("%s\n", winner.name);
        printf("%s\n", second.name);
    }
    else
    {
        printf("%s\n", winner.name);
    }
}