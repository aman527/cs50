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
int strength(pair given);

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
    // Loop through candidates to find who was voted for
    for (int i = 0; i < candidate_count; i++)
    {
        // If the correct candidate is found
        if (strcmp(name, candidates[i]) == 0)
        {
            // Set the voter's vote #rank to the idx of the chosen candidate
            ranks[rank] = i;
            return true;
        }
    }
    // If no candidate is found, indicate invalid vote
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loop from highest preference candidate (i) to lowest
    for (int i = 0; i < candidate_count; i++)
    {
        int preferred_idx = ranks[i];
        // Loop over the lower preference (relative to candidate i) candidates
        for (int j = i + 1; j < candidate_count; j++)
        {
            int less_preferred_idx = ranks[j];
            preferences[preferred_idx][less_preferred_idx]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    // Loop over the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Loop over the competitors to candidate i
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Get the number who prefer candidate i over j
            int for_ = preferences[i][j];
            // And who prefer j over i
            int against = preferences[j][i];
            pair candidate_pair;
            // If they are tied, don't add the pair to the array
            if (for_ == against)
            {
                continue;
            }
            // If candidate i is the winner
            else if (for_ > against)
            {
                candidate_pair.winner = i;
                candidate_pair.loser = j;

            }
            // If candidate j is the winner
            else
            {
                candidate_pair.winner = j;
                candidate_pair.loser = i;
            }
            // Update the pairs
            pairs[pair_count] = candidate_pair;
            // Increment pair_count
            pair_count++;
        }
    }
    return;
}
// Return the midpoint idx of a pair_array with given length
int midpoint_idx(int length)
{
    // If the array is of odd length, make the left half smaller
    if (length % 2 == 1)
    {
        return (length - 1) / 2;
    }
    return length / 2;
}
// Return the strength of victory of a given pair
int strength(pair given)
{
    return preferences[given.winner][given.loser];
}
// Compare the two pairs to find the one with the greater victory strength
int compare(pair left, pair right)
{
    // If the left pair has a greater victory strength
    if (strength(left) > strength(right))
    {
        // Return 1 for the right pair
        return 0;
    }
    // If the right pair has a greater strength OR if they're the same
    else
    {
        // Return 0 for the right pair
        return 1;
    }
}
// My implementation of merge sort (maybe it's inefficient, but it's what I came up with!)
void sort(pair array[], int length)
{
    // Check the length of the array
    if (length == 1)
    {
        return;
    }

    // Divide the array into a left and right half
    int mid = midpoint_idx(length);
    int len_left = mid;
    int len_right = length - mid;

    pair left[len_left];
    pair right[len_right];

    // Populate the left and right arrays
    for (int i = 0; i < len_left; i++)
    {
        left[i] = array[i];
    }
    for (int i = mid; i < length; i++)
    {
        right[i - mid] = array[i];
    }

    // Sort each half individually
    sort(left, len_left);
    sort(right, len_right);

    // Merge the two halves

    int left_idx = 0, right_idx = 0;
    // Iterate over the elements of the array
    for (int i = 0; i < length; i++)
    {
        pair current_left = left[left_idx];
        pair current_right = right[right_idx];
        // If the program reaches the end of one of the halves, take the lowest element from the other half
        if (left_idx >= len_left)
        {
            array[i] = current_right;
            right_idx++;
            continue;
        }
        else if (right_idx >= len_right)
        {
            array[i] = current_left;
            left_idx++;
            continue;
        }
        // Otherwise, compare the two pairs, current_left and current_right
        if (compare(current_left, current_right) == 0)
        {
            // If the left pair had a stronger victory
            array[i] = current_left;
            left_idx++;
        }
        else
        {
            // If the right pair was stronger OR if it was a tie
            array[i] = current_right;
            right_idx++;
        }
    }
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    sort(pairs, pair_count);
    return;
}
// Recursively check if there is a path leading from the current_node to the goal node
bool does_path_exist(int current_node, int goal_node)
{
    // Declare an array of all the nodes connected
    int connected[candidate_count];
    int num_connected = 0;
    // Populate the array
    for (int i = 0; i < candidate_count; i++)
    {
        // If there is an edge between the current node and the ith node
        if (locked[current_node][i])
        {
            // Check if there is a direct connection between the current node and the goal node
            if (i == goal_node)
            {
                return true;
            }
            // Otherwise, just add it to the connected array
            connected[num_connected] = i;
            num_connected++;
        }
    }
    // For every node i that's connected to current_node, check if a path exists from node i to goal_node
    for (int i = 0; i < num_connected; i++)
    {
        int new_node = connected[i];
        if (does_path_exist(new_node, goal_node))
        {
            return true;
        }
    }
    return false;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int w = pairs[i].winner, l = pairs[i].loser;
        // Lock in the edge only if there is no existing path from the loser to the winner
        if (!does_path_exist(l, w))
        {
            locked[w][l] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool is_source[candidate_count];
    // Initialize all source values as true
    for (int i = 0; i < candidate_count; i++)
    {
        is_source[i] = true;
    }
    // For a node to be a source, its whole *column* must be false
    // Meaning there are no nodes with edges pointing at it
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If there is a node j with an edge pointing at node i, node i cannot be the source
            if (locked[j][i])
            {
                is_source[i] = false;
                break;
            }
        }
    }
    // Find the first candidate with an is_source value of true
    for (int i = 0; i < candidate_count; i++)
    {
        if (is_source[i])
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}
