#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define MAX 9

typedef struct{

    char *name;
    int votes;

}candidate;

//array of candidates
candidate candidates[MAX];

//number of candidates
int candidate_count;

//functions
bool vote(char *name);
void print_winner();

int main(int argc, char *argv[]){
    //Plurality vote
        //every voter chooses one candidate
        //whichever candidate has the msot votes wins

    //./plurality Alice Bob Charlie
    //Number of voters : 4
    //Vote: Alice
    //Vote: Bob
    //Vote: Charlie
    //Vote: Charlie
    //Charlie

//2 functions
    //vote
        //look for a candidate called name.
        //if candidate found, update their vote total and return true.
        //if no candidate found, dont update any vote totals and return false
    //print_winner
        //print the name of the candidate(s) who have the most votes.

    //check for invalid usage
    if(argc < 2){
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    //populate array of candidates
    //check for error
    candidate_count = argc - 1;
    if(candidate_count > MAX){
        printf("Maxium number of candidates is %i\n", MAX);
        return 2;
    }

    for(int i = 0; i < candidate_count; i++){
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    //prints array
    /*for(int i = 0; i < candidate_counts; i++){
        printf("%i %s %i\n", i, candidates[i].name, candidates[i].votes);
    }*/

    //receive number of voters
    int voters = get_int("Number of voters: ");

    //iterate and check for invalid votes
    for(int i = 0; i < voters; i++){
        char *name = get_string("Vote: ");
        if(!vote(name)){
            printf("Invalid vote.\n");
        }
    }

    print_winner();
    return 0;

}

bool vote(char *name){

    for(int i = 0; i < candidate_count; i++){
        if(strcmp(name, candidates[i].name) == 0){
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

void print_winner(){

    //finds the highest votes
    int highest = 0;
    for(int i = 0; i < candidate_count; i++){
        if(candidates[i].votes > highest) highest = candidates[i].votes;
    }

    //prints highest voters
    for(int i = 0; i < candidate_count; i++){
        if(candidates[i].votes == highest) printf("%s\n", candidates[i].name);
    }
    return;
}