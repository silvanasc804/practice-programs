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
} pair;

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
        // names of each of the candidates
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs and preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
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
    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if candidate's name matches given name
        if (strcmp(name, candidates[i]) == 0)
        {
            // Increment candidate's votes and return true
            ranks[rank] = i;
            return true;
        }
    }
    // If no match
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Take the first candidate to compare
    for (int i = 0; i < candidate_count; i++)
    {
        // Take the second candidate to compare
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
    pair_count = 0;
    // Take the first candidate to compare
    for (int i = 0; i < candidate_count; i++)
    {
        // Take the second candidate to compare
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] <
                preferences[pairs[j].winner][pairs[j].loser])
            {
                // Swap the tow data structures
                temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    bool not_cycle = true;
    int t_winner;
    int t_loser;
    int row;
    // Takes one pair at a time
    for (int i = 0; i < pair_count; i++)
    {
        row = 0;
        t_loser = pairs[i].loser;
        t_winner = pairs[i].winner;
        while (not_cycle)
        {
            if (locked[row][t_winner] == true)
            {
                if (row == t_loser)
                {
                    not_cycle = false;
                }
                else
                {
                    // Starts the loop agin
                    t_winner = row;
                    row = 0;
                }
            }
            else
            {
                if (row < candidate_count)
                {
                    row++;
                }
                else
                {
                    break;
                }
            }
        }

        if (not_cycle)
        {
            // add the edge
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        not_cycle = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool has_incoming_edge;
    for (int col = 0; col < candidate_count; col++)
    {
        has_incoming_edge = false;
        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][col])
            {
                has_incoming_edge = true;
                break;
            }
        }
        if (!has_incoming_edge)
        {
            printf("%s\n", candidates[col]);
        }
    }
    return;
}
