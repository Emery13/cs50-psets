#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
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
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

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
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

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
                    printf("%s\n", candidates[i].name);
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

    for (int i = 0; i < candidate_count; i++)
    {
        // check if name corresponds to a candidate name
        if (!strcmp(name, candidates[i].name))
        {
            // if yes, update global preferences array
            preferences[voter][rank] = i;

            // then, return 'true'
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int rank = 0, test = 0;

    for (int i = 0; i < voter_count; i++)
    {
        rank = 0;
        
        while (true)
        {
            if (candidates[preferences[i][rank]].eliminated == false)
            {
                // if no, update that candidate's vote count by 1
                candidates[preferences[i][rank]].votes++;
                break;
            }
            else
            {
                rank++;
            }
        }
    }
    
    return;

//    void recursive_vote_count(int voter, int rank)
//    {
//        // check if voters' preferences have been eliminated
//        if (candidates[preferences[voter][rank]].eliminated == false)
//        {
//            // if no, update that candidate's vote count by 1
//            candidates[preferences[voter][rank]].votes++;
//        }
//        else
//        {
//            // else, check the voter's next preference
//            recursive_vote_count(voter, rank + 1);
//        }
//
//        return;
//    }

    // Recursive check :
    // OK loop through voters
    // OK pick 1st voter
    // OK Has ith preference been eliminated?
    // OK  => if no, add 1 vote to that candidate's vote countbreak the loop and go to next voter
    //     => if yes, call recursive function on i+1th preference
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate has more than half the votes, then print its name and return true
        if (candidates[i].votes > ((float) voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // if no candidate has more than half the vote, return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int still_running = 0;
    int candidates_min_votes = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        // get the number of candidates not eliminated
        if (candidates[i].eliminated == false)
        {
            still_running++;
            // for every candidates remaining, check the number of candidates having the mininmum number of votes
            if (candidates[i].votes == min)
            {
                candidates_min_votes++;
            }
        }
    }
    
    // check if the number of candidates with min number of votes == number of candiates still running
    if (still_running == candidates_min_votes)
    {
        // it yes, return true
        return true;
    }
    
    // return false otherwise
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // loop through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate's number of vote == min
        if (candidates[i].votes == min)
        {
            // then, change eliminated value to 'true'
            candidates[i].eliminated = true;
        }
    }
    return;
}
