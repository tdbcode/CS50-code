#include <cs50.h>
#include <stdio.h>
#include <string.h>


/*
This was a tough task so I did research a lot surrounding the lock_pairs functions of Tideman. Below are the sources I used to help with understanding
after trying multiple attempts using nested for loops and functions before trying recursion.

I realised from this link that recursion made sense:
https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9

Recursion source and explanation although I have done fibonacci before, I just wanted further examples in C:
https://www.scaler.com/topics/c/recursion-in-c/

Helping to test the algorithm and create test text files:
https://tideman.netlify.app/

*/

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
//bool checkcycle(pair p);
bool checkcycle(int startcandidate, int endcandidate);

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
            // printf("%s %i\n", name,  ranks[rank]); // Output list item for testing.
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
        // Iterate through losers in preferences without repeating checks in preference array (l = w + 1)
        for (int l = w + 1; l < candidate_count; l++)
        {
            //printf("Candidate : %i vs %i \n", w, l); //For testing and tracing only
            // Note to self: There can't be a [0][0] because it's the same candidate, also can't be a [1][1] either as this is a duplicate candidate and so on.
            // If [winner][loser], e.g. [0][1] is more than [loser][winner], e.g. [1], [0] then
            // Nothing to run if there is a draw, a pair is not added
            // If first preference of people who prefer w to l is more than those who prefer l to w then
            if (preferences[w][l] > preferences[l][w])
            {
                pairs[pair_count].winner = w;           // Add current winner to current pair in pair array
                pairs[pair_count].loser = l;            // And add the loser as loser to current pair in pair array
                pair_count++;                           //Have to add one to paircount so total number of pairs is known
            }
            else if (preferences[w][l] < preferences[l][w]) // If the opposite, save as reverse
            {
                pairs[pair_count].winner = l;               // Add next items winner, as winner in current pair
                pairs[pair_count].loser = w;                // Add current loser as loser of current pair
                pair_count++;                               //Have to add one to paircount so total number of pairs is known
            }
            //      printf("Pair: %i Winner : %i Loser: %i \n", pair_count, pairs[pair_count - 1].winner,
            //      pairs[pair_count - 1].loser); //For testing and tracing only
        }
    }

}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;
    bool flag = true; //Flag to symbolise if a switch has been made, if so continue bubble sort
    int back = pair_count - 1; // Set back of array for end of loop

    // Use bubblesort to compare pairs
    while (flag)
    {
        flag = false; // No switches made yet

        //Perform bubble sort on pairs array
        for (int p = 0; p <= back; p++)
        {
            // comparing the current winner strength is less than next winner strength then switch items
            // Compare to next item in the array to perform bubble sort
            if ((preferences[pairs[p].winner][pairs[p].loser]) < (preferences[pairs[p + 1].winner][pairs[p + 1].loser]))
            {
                temp = pairs[p];
                pairs[p] = pairs[p + 1];
                pairs[p + 1] = temp;
                flag = true; // Switches has been made, loop needs to run again
            }
        }
        back -= 1; // minus one from back of array as it is already sorted and doesn't need to be checked again
    }

    /* used for tracking and testing only - outputting list
    for (int i = 0; i < pair_count; i++)
    {
        printf("Winner: %i Loser: %i\n", pairs[i].winner, pairs[i].loser);
    }*/
}

bool checkcycle(int startcandidate, int endcandidate)
{
    // int startcandidate = p.winner;
    // int endcandidate = p.loser;
    bool result = 0;
    // if the loser is the same as the winner then we know there is a cycle, this ends recursive function
    if (locked[endcandidate][startcandidate])
    {
        return true;
    }

    //for every candidate
    for (int c = 0; c < candidate_count; c++)
    {
        // check if end candidate vs current has an edge
        if (locked[endcandidate][c])
        {
            result = checkcycle(startcandidate, c); //if so current candidate with start candidate in recursive function
            //printf("%i", result);
            if (result) // if true, return true
            {
                return true;
            }
        }
    }

    return false; // if no edge found above then return false

    // Repeat for each candidate
    /*
    Does A go to D?
    Does B go to D?
    Does C go to D?
    */
    /* Redundant, didn't work
    for (int c = 0; c < candidate_count; c++)
    {
        // need to compare winner with all other winners
        if(locked[c][startcandidate])
        {
            startcandidate = c;
            break;
        }
    } */
}

// Lock pairs into the candidate graph in order, without creating cycles
// Source used for the lock_pair function only, as I was stuck and couldn't work this out:
// https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9
void lock_pairs(void)
{
    int startcandidate = 0;
    int endcandidate = 0;
    bool result = 0;
    // Repeat for each pair
    for (int p = 0; p < pair_count; p++)
    {
        startcandidate = pairs[p].winner;
        endcandidate = pairs[p].loser;
        result = checkcycle(startcandidate, endcandidate); //get result from checkcycle method
        //printf("%i", result);
        //result = checkcycle(pairs[p]); //get result from checkcycle method

        if (result == 0)
        {
            locked[startcandidate][endcandidate] = true;
        }
    }
    return;

//   startcandidate = pairs[p].winner;
//   endcandidate = pairs[p].loser;
// Repeat for each candidate
    /*   for (int c = 0; c < candidate_count; c++)
        {
            if (!(startcandidate == endcandidate))
            {
                locked[pairs[p].winner][pairs[p].loser] = true;
            }
            else if (endcandidate == startcandidate)
            {
                locked[pairs[p].winner][pairs[p].loser] = false;
                startcandidate = pairs[c].winner;
                endcandidate = pairs[c].loser;
            }
        } */

// For testing, output locked array
    /* for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
        printf("%d ", locked[i][j]);
        }
        printf("\n");
    }*/
}

// Print the winner of the election
void print_winner(void)
{
    int candidatesfalses[candidate_count]; // Array to count all candidate falses in locked array
    for (int a = 0; a < candidate_count; a++)
    {
        candidatesfalses[a] = 0;
    }
    // Loop through all candidates to check for falses
    for (int c = 0; c < candidate_count; c++)
    {
        for (int d = 0; d < candidate_count; d++)
        {
            // if locked is equal to false means no edge
            if (locked[d][c] == false)
            {
                candidatesfalses[c]++; //count falses for current candidate
            }
        }
    }

    for (int w = 0; w < candidate_count; w++)
    {
        //printf("Name: %s Falses: %i\n", candidates[w], candidatesfalses[w]); // For testing purposes
        // if candidates falses equals candidate count they must be the winner so output them from candidate list
        if (candidatesfalses[w] == candidate_count)
        {
            printf("%s\n", candidates[w]);
            break;
        }
    }
    return;
}