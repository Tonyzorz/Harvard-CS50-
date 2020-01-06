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
    //- look for a candidate called name
	//- if candidate found, update ranks and return true. ranks[i] is the voter's ith preference.
	//- if no candidate found, dont update any ranks and return false.
    // TODO

    for(int i = 0; i < candidate_count; i++){
        if(strcmp(candidates[i], name) == 0){
            ranks[i] = rank;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //- update the preferences array based on the current voter's rank
    // TODO

    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            if(ranks[i] < ranks[j]) preferences[i][j] += 1;
        }
    }

    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            printf("%i\t", preferences[i][j]);
        }
        printf("\n");
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
  //  - add each pair of candidates to pairs array if one candidate is preferred over the other.
//	- udpate global variable pair_count to be the total number of pairs

    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            if(preferences[i][j] > preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
            /*else if(preferences[i][j] < preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }*/

        }
    }

    //before sort
    for(int i = 0; i < pair_count; i++){
        printf("pairs %ith is winner %i and loser %i\n", i, pairs[i].winner, pairs[i].loser);
    }
    printf("\n");
    // TODO
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    //bubble sort
    //backwards, placing the highest value first
    for(int i = 0; i < pair_count - 1; i++){
        int ifirstDiff = preferences[pairs[i].winner][pairs[i].loser];
        int isecondDiff = preferences[pairs[i].loser][pairs[i].winner];
        int iComp = ifirstDiff - isecondDiff;

        for(int j = i + 1; j < pair_count; j++){
            int jfirstDiff = preferences[pairs[j].winner][pairs[j].loser];
            int jsecondDiff = preferences[pairs[j].loser][pairs[j].winner];
            int jComp = jfirstDiff - jsecondDiff;

            if(iComp < jComp){
                pair temp = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = temp;
            }
        }
    }

    for(int i = 0; i < pair_count; i++){
        printf("pairs %ith is winner %i and loser %i\n", i, pairs[i].winner, pairs[i].loser);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //- update locked to create the locked graph by adding all edges
    //in decreasing order of vicotry strength, as long as there is no cycle
    // TODO
    locked[pairs[0].winner][pairs[0].loser] = true;
    for(int i = 1; i < pair_count; i++){
        int a = pairs[i].winner;
        int b = pairs[i].loser;
        for(int j = i + 1; j < pair_count; j++){
            int z = pairs[j].winner;

            if(a > z) locked[a][b] = true;
            else break;
        }

    }

    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            printf("%s\t", locked[i][j] ? "true" : "false");
        }
        printf("\n");
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    //-print out the winner of the election, who will be the source of the graph
	//- you may assume there may be no more than one source.
    int count = 0;
    int winner = 0;
    for(int i = 0; i < pair_count; i++){
        int temp = 0;
        for(int j = 0; j < pair_count; j++){
            if(locked[i][j]) {
                temp ++;
                if(count < temp){
                    count = temp;
                    winner = i;
                } else if (count == temp){
                    winner = i;
                }
            }
        }
    }

    printf("%s\n", candidates[winner]);
    // TODO
    return;
}

/*bool lockrecursive(int winner, int loser){

    bool check = true;
    if(winner < 0){
        winner = 0;
        return true;
    }
    if(loser < 0){
        loser = 0;
        return true;
    }

    for(int i = 0; i < winner; i++){
        if(locked[winner][i]) check = false;
    }
}*/
