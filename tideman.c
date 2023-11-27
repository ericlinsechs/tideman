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
    for (int i = 0; i < candidate_count; i++) {
        if (!strcmp(candidates[i], name)) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++)
            preferences[ranks[i]][ranks[j]]++;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (i == j || preferences[i][j] <= preferences[j][i])
                continue;

            pairs[pair_count].winner = i;
            pairs[pair_count++].loser = j;
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int margins[pair_count];

    for (int i = 0; i < pair_count; i++) {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        margins[i] = preferences[winner][loser] - preferences[loser][winner];
    }

    for (int i = 0; i < pair_count - 1; i++) {
        for (int j = 0; j < pair_count - i - 1; j++) {
            if (margins[j] < margins[j + 1]) {
                pair tmp_p = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = tmp_p;

                int tmp_s = margins[j];
                margins[j] = margins[j + 1];
                margins[j + 1] = tmp_s;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int cycle_list[candidate_count];
    int cw_cnt = 0;
    int tmp_loser = -1;

    for (int i = 0; i < pair_count; i++) {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // Iterate list to compare with the current loser
        bool w_flag = false, l_flag = false;
        for (int i = 0; i < cw_cnt; i++) {
            if (cycle_list[i] == winner)
                w_flag = true;
            if (cycle_list[i] == loser)
                l_flag = true;
            if (w_flag && l_flag)
                goto lock_pairs_continue;  // Detect cycle
        }

        if (tmp_loser == winner) {
            // Add both winner and loser to the list
            if (!cw_cnt) {
                cycle_list[cw_cnt++] = pairs[i - 1].winner;
                cycle_list[cw_cnt++] = winner;
            }
            cycle_list[cw_cnt++] = loser;
        }

        locked[winner][loser] = true;

    lock_pairs_continue:
        tmp_loser = loser;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    /* The final winner */
    int final_w = -1;

    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (locked[i][j]) {
                if (final_w == -1)
                    final_w = i;
                else {
                    /* Replace with the new winner */
                    if (j == final_w)
                        final_w = i;
                }
            }
        }
    }

    printf("%s\n", candidates[final_w]);

    return;
}
