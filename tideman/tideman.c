#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Loops through all candidates
    for (int c = 0; c < candidate_count; c++)
    {
        if (strcmp(name, candidates[c]) == 0) // if name entered matches a candidate
        {
            ranks[rank] = c; // Record index into rank array in rank location
            // printf("%s %i\n", name,  ranks[rank]); // Output List for testing.
            return true;
            break;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Current winner of pair
    for (int w = 0; w < candidate_count; w++)
    {
        // Jump one down the list from above as there is no need to check previous value as it's the same person or already lost
        for (int l = w + 1; l < candidate_count; l++)
        {
            preferences[ranks[w]][ranks[l]]++; // Add one to winner vs loser in ranking for preferences
            //printf("Candidate : %i vs %i : %i\n", w, l, preferences[w][l]); // Output List for testing.
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iterate through winners in preferences
    for (int w = 0; w < candidate_count; w++)
    {
        // Iterate through losers in preferences
        for (int l = 1; l < candidate_count; l++)
        {
            printf("Candidate : %i vs %i \n", w, l);
            // Note to self: There can't be a [0][0] because it's the same candidate
            // If [winner][loser], e.g. [0][1] is more than [loser][winner], e.g. 1, 0 then
            if (preferences[w][l] > preferences[l][w])
            {
                pairs[w].winner = w;
                pairs[l].loser = l;
            }
            else if (preferences[w][l] < preferences[l][w])
            {
                pairs[w].winner = l;
                pairs[l].loser = w;
            }
           // printf("Candidate : %i vs %i \n", pairs[w].winner, pairs[l].loser);
        }
    }

}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}