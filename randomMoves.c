// A demonstration of how to use rand to generate data
// We use it here to generate row,column ints within 
// range 0..4 which are suitable for assignment 2 input
// We keep track of which moves we have already randomly
// generated and only print out the unique ones.

// To get random moves run like
// ./randomMoves

// To generate repeatable 'random' moves run with a 
// particular seed eg
// ./randomMoves 42


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 5
#define NUM_MOVES (GRID_SIZE*GRID_SIZE)

int main(int argc, char * argv[]){
    //Grid to keep track of moves we have seen already
    int moves[GRID_SIZE][GRID_SIZE] = {{0}};
 
    if ( argc == 1 ){
        srand(time(NULL));
    } else {
       int seed = atoi(argv[1]);
       srand(seed);
    }
    
    
    int uniqueMoves = 0;
       

    while ( uniqueMoves < NUM_MOVES ) {
       int row = rand()% GRID_SIZE;  //generate a random int between 0..4
       int col = rand()% GRID_SIZE;  //generate a random int between 0..4
       
       //If we have not seen this move before
       //mark it with the value 1, print it out
       //and increment the number of unique moves
       
       if(moves[row][col] == 0 ){
           moves[row][col] = 1;
           printf("%d %d\n",row,col);      
           uniqueMoves = uniqueMoves + 1;
       } 
    }

}
