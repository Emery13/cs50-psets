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

//ADDED
bool cycles_check(int winner, int loser);

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
    // check if name is a match for the name of a valid candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // if it's a match, update the ranks array
            ranks[rank] = i;
            return true;
        }
    }
    
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            //preferences[ranks[i]][ranks[j]]++;
            if (preferences[i][j] != preferences[j][i])
            {
                // check which is highest, [i][j] or [j][i]
                if (preferences[i][j] > preferences[j][i])
                {
                    // add pair
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                }
                else
                {
                    // add pair
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                }
                // update pair_count
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // initialize a buffer variable
    int buffer_winner = 0, buffer_loser = 0;
    int max = 0, address = 0;

    for (int j = 0; j < pair_count; j++)
    {
        max = 0, address = 0;

        for (int i = j; i < pair_count; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] > max)
            {
                max = preferences[pairs[i].winner][pairs[i].loser];
                address = i;
            }
        }

        buffer_winner = pairs[j].winner;
        buffer_loser = pairs[j].loser;
        
        pairs[j].winner = pairs[address].winner;
        pairs[j].loser = pairs[address].loser;
        
        pairs[address].winner = buffer_winner;
        pairs[address].loser = buffer_loser;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // go through all pairs
    for (int i = 0; i < pair_count; i++)
    {
        // run a recursive function to check for loops
        if (!cycles_check(pairs[i].winner, pairs[i].loser))
        {
            // if there are no loops, add the lock
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

bool cycles_check(int winner, int loser)
{
    // check if there is a lock already from the looser to the winner
    if (locked[loser][winner] == true)
    {
        // if yes, return true to prevent the new lock
        return true;
    }

    // go through each candidates to recursively check for a loop from each one
    for (int i = 0; i < candidate_count; i++)
    {
        // check if there is a lock from any other candidate to the winner
        if (locked[i][winner] == true)
        {
            // if yes, recursively check for a loop
            return cycles_check(i, loser);
        }
    }
    
    // if no loops exist, return false
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // create an array with the same size as the number of candidates
    int array[candidate_count];
    
    for (int l = 0; l < candidate_count; l++)
    {
        array[l] = 0;
    }
    
    // go through the locked matrix and check which candidate doesn't have an edge pointing at him
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                array[j]++;
            }
        }
    }
    
    for (int k = 0; k < candidate_count; k++)
    {
        if (array[k] == 0)
        {
            printf("%s\n", candidates[k]);
        }
    }
    return;
}

