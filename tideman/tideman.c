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
        for (int l = w + 1; l < candidate_count; l++)
        {
            //printf("Candidate : %i vs %i \n", w, l); //For testing and tracing only
            // Note to self: There can't be a [0][0] because it's the same candidate, also can't be a [1][1] either as this is a duplicate candidate and so on.
            // If [winner][loser], e.g. [0][1] is more than [loser][winner], e.g. 1, 0 then
            if (preferences[w][l] > preferences[l][w]) // If current winner is more than the loser in preferences array then
            {
                pairs[pair_count].winner = w;           // Add current winner to current pair in pair array
                pairs[pair_count].loser = l;            // And add the loser as loser to current pair in pair array
                pair_count++;                //Have to add one to paircount so total number of pairs is known
            }
            else if (preferences[w][l] < preferences[l][w]) // If the opposite
            {
                pairs[pair_count].winner = l;               // Add next items winner, as winner in current pair
                pairs[pair_count].loser = w;                // Add current loser as loser of current pair
                pair_count++;                           //Have to add one to paircount so total number of pairs is known
            }
            printf("Pair: %i Winner : %i Loser: %i \n", pair_count, pairs[w].winner, pairs[l].loser); //For testing and tracing only
        }
    }

}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int tempWinner = 0;
    int tempLoser = 0;
    bool flag = true; //Flag to symbolise if a switch has been made, if so continue bubble sort

    // Use bubblesort to compare pairs
    while (flag)
    {
        flag = false; // No switches made yet

        //Perform bubble sort on pairs array
        for (int p = 0; p < pair_count; p++)
        {
            if (pairs[p].winner < pairs[p + 1].winner)
            {
                tempWinner = pairs[p + 1].winner;
                tempLoser = pairs[p + 1].loser;
                pairs[p + 1].winner = pairs[p].winner;
                pairs[p + 1].loser = pairs[p].loser;
                pairs[p].winner = tempWinner;
                pairs[p].loser = tempLoser;
                flag = true; // Switches has been made, loop needs to run again
            }
        }
    }


    for (int i = 0; i < pair_count; i++)
    {
        printf("Winner: %i Loser: %i\n", pairs[i].winner, pairs[i].loser);
    }
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