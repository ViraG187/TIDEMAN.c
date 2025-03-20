#include<stdio.h>
#include<string.h>
#include<stdbool.h>

typedef struct {
    int winner;
    int loser;
}pairs;

int candidate_count;
int preferences[100][100];
pairs pair[10*10];
bool locked[100][100];    //declaring array size at top to use ahead
int pair_count=0;
char* cand[100];

void lock_pairs(void);
bool cycle(int winner, int loser);
void short_pairs(void);
void add_pairs(void);
void record_preferences(int ranks[]);
bool vote(int rank,char* name,int ranks[]);
int print_winner(void);

int main(int argc, char* argv[]){
    candidate_count = argc-1;
    
    for(int i=0; i<candidate_count ; i++){
        cand[i]=argv[i+1];
        //printf("%20s \n",cand[i]);
    }
    for(int i=0; i<candidate_count; i++){
        for(int j=0; j<candidate_count;j++){
            locked[i][j] = false; // initialitze without edge in graph
        }
    }
    int pair_count = 0;
    int voters;
    printf("Enter number of Voters: \n");
    scanf("%d", &voters);
    for(int i = 0; i<voters; i++){
        int ranks[candidate_count];
        for(int j =0; j<candidate_count;j++){
            printf("Rank %i : ",j+1);
            char name[20];
            scanf("%20s",name);
            if(!vote(j,name,ranks)){
                printf("Invalid Vote\n");
            }
        } printf("\n");
        record_preferences(ranks);
    }
    
    add_pairs(); //make pairs of candidate
    short_pairs(); //short between pairs
    lock_pairs(); //lock to avoid cycle graph
    print_winner();
}
bool vote(int rank,char* name,int ranks[]){

    for(int i=0 ; i < candidate_count ;i++){

        if(strcmp(cand[i],name)==0){
            ranks[rank] = i; //update ranks[];
            return true;
        }
    }    
    return false;

}
void record_preferences(int ranks[]){

    for(int i=0 ; i < candidate_count-1; i++){
        for(int j=i+1; j < candidate_count; j++){
            preferences[ranks[i]][ranks[j]] ++; 
        }
    }
}
void add_pairs(void){
    int strength;
    for(int i=0 ; i < candidate_count-1; i++){
        for(int j=i+1; j < candidate_count; j++){

            strength = preferences[i][j] - preferences[j][i];
            if(strength > 0){
                pair[pair_count].winner = i;
                pair[pair_count].loser = j;
                pair_count++;
            } else if(strength < 0){
                pair[pair_count].winner = j;
                pair[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}
void short_pairs(void){
    for(int i =0; i <pair_count-1; i++){ // checking high using selection sort
        int margin_high = preferences[pair[i].winner][pair[i].loser] - preferences[pair[i].loser][pair[i].winner];
        int temp_margin;
        int margin_high_index = i;
        for( int j=i+1; j<pair_count; j++){
            temp_margin = preferences[pair[j].winner][pair[j].loser] - preferences[pair[j].loser][pair[j].winner];
            if(margin_high < temp_margin){
                margin_high = temp_margin;
                margin_high_index = j;
                
            }
        }if(margin_high_index != i) {     //swaping positions by changing index
            pairs buffer = pair[i] ;
            pair[i] = pair[margin_high_index];
            pair[margin_high_index] = buffer;
        }
    } return;
}
bool cycle(int winner, int loser){
    if (winner == loser){
        return true;
    }
    
    for(int i = 0; i < candidate_count; i++){
        if(locked[loser][i] && cycle(winner,i)){ 
          return true;
        }
    }
    return false;
        
}
void lock_pairs(void){
    for (int i =0; i < pair_count;i++){
        if(!cycle(pair[i].winner,pair[i].loser)){
            locked[pair[i].winner][pair[i].loser] = true;
        }
    }

}
int print_winner(void){
    for(int i=0; i<candidate_count;i++){
        bool source = true;
        for(int j=0; j<candidate_count; j++){
            if(locked[j][i]){ // Hare[i]->Krishna[j] then we need to check if it has krishna[j]->Hare[i] if has arrow then not source
                source = false;
                break;
            }
        }
        
        if(source){
            printf("Winner is %s", cand[i]);
        }
    }

}
