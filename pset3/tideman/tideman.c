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
bool is_closed_loop(int start, int winner, int loser);


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
    for (int i = 0; i < candidate_count; i++)
    {
        // check if the name is a match
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}




// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // loop through the preference array
    for (int i = 0; i < candidate_count; i++)
    {
        // update the preferences if a candidate is higher on the rank list
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] ++;
        }
    }
    return;
}




// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + i; j < candidate_count; j++)
        {
            // update the pairs if a winner exists
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}




// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // get the strength of victory
    int score[pair_count];
    int score_winner = 0;
    int score_loser = 0;

    for (int i = 0; i < pair_count; i++)
    {
        score_winner = preferences[pairs[i].winner][pairs[i].loser];
        score_loser = preferences[pairs[i].loser][pairs[i].winner];
        score[i] = score_winner - score_loser;
    }

    int temp_score;
    pair temp_pair;

    // sort the pairs by strenght
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            // swap pairs to move the one with the most votes first
            if (score[j] <= score[i])
            {
                // swap scores
                temp_score = score[i];
                score[i] = score[j];
                score[j] = temp_score;
                // swap pairs
                temp_pair = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp_pair;
            }
        }
    }
    return;
}




// check if a closed loop is formed
bool is_closed_loop(int start, int winner, int loser)
{
    // check the locked table if the candidate is the start of an arrow
    for (int i = 0; i < pair_count; i++)
    {
        // check if a arrow starts there
        if (locked[loser][i] == true)
        {
            // check if that arrow forms a loop
            if (i == start)
            {
                return true;
            }

            // check if that block has another arrow
            // and propagate the error
            if (is_closed_loop(start, loser, i) == true)
            {
                return true;
            }
        }
    }
    // no loop is formed
    return false;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // check recursivly if the arrow for a loop
        if (is_closed_loop(pairs[i].winner, pairs[i].winner, pairs[i].loser) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}




// Print the winner of the election
void print_winner(void)
{
    bool has_lost;
    for (int i = 0; i < candidate_count; i++)
    {
        // reset the variable
        has_lost = false;

        // checked if the candidate has lost against anybody
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                has_lost = true;
                break;
            }
        }

        // if the candidate has not lost, the name is displayed
        if (has_lost == false)
        {
            printf("%s\n", candidates[i]);
        }
    }
}
