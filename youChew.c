/**
 * Author      : Pua Qie Shang
 * Student ID  : z5157686
 * Assignment  : You Chew
 * This program finds the maximum score of a game called You Chew,
 * which is played by rolling a 9-sided dice five times.
 * Valid rules and conditions are present in this game
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 5
#define SIZE_OF_TALLY 10

#define ONE_PAIR 1
#define TWO_PAIRS 2
#define TRIPLE 3
#define FOURS 4
#define FIVES 5
#define FULLHOUSE 6 //1 pair and 1 triple

// Prototypes
int scanNumbers(int array[SIZE]);
int invalidInput(int n, int array[SIZE]);
void digitCount(int array[SIZE], int tally[SIZE_OF_TALLY]);

// Protoypes to give the number in array 
// which is a pair, triple, or quad
int pair1Number (int tally[SIZE_OF_TALLY]);
int pair2Number (int tally[SIZE_OF_TALLY], int pair1Num);
int tripleNumber(int tally[SIZE_OF_TALLY]);
int quadNumber(int tally[SIZE_OF_TALLY]);

// Prototypes to determine which rule should be used 
int whichRule (int tally[SIZE_OF_TALLY]);
int onePair(int tally[SIZE_OF_TALLY]);
int twoPairs(int pair1Num, int pair2Num);
int triple(int tally[SIZE_OF_TALLY]);
int quad(int tally[SIZE_OF_TALLY]);
int fullhouse(int tally[SIZE_OF_TALLY]);
int sumScore(int array[SIZE]);

// Prototypes to find longest sequence
int longestSeq(int array[SIZE]);
void count(int array[SIZE], int min, int max, int seqTally[]);
int max(int array[SIZE]);
int secondMax(int array[SIZE]);
int min(int array[SIZE]);
int secondMin(int array[SIZE]);
int seq4Type(int min, int tally[SIZE_OF_TALLY]);
int seqSum (int seqLength, int ruleType, int seq4,
            int secondHighestNum, int max);

int main(int argc, char*argv[]) {

   int array[SIZE]; 
   int tally[SIZE_OF_TALLY];
   int isInputValid;
   
   isInputValid = scanNumbers(array);
   int successOrFail = invalidInput(isInputValid, array);
   
   // If all inputs are valid (success), countinue with the program
   if (successOrFail == EXIT_SUCCESS) {
      
      digitCount(array, tally);
      
      // Gives the numbers of pairs, triples, and fours
      int pair1Num = pair1Number(tally);
      int pair2Num = pair2Number(tally, pair1Num);
      int tripleNum = tripleNumber(tally);
      int quadNum = quadNumber(tally);
      
      // Gives the score based on the rule applied             
      int ruleType = whichRule(tally);
      int onePairScore = onePair(tally);
      int twoPairsScore = twoPairs(pair1Num, pair2Num);
      int tripleScore = triple(tally);
      int quadScore = quad(tally);
      int fivesScore = 17 + array[0]*5;
      int fullhouseScore = fullhouse(tally);
      int sum = sumScore(array); 
      
      // Gives the score depending on the sequence length
      int seqLength = longestSeq(array);  
      int secondHighestNum = secondMax(array);
      int secondSmallestNum = secondMin(array);
      int seq4 = seq4Type(min(array),  tally);
      // Gives the score if there are 4+ sequential dice faces
      int seqScore = seqSum(seqLength, ruleType, seq4,
                            secondHighestNum, max(array)); 

      /** 
       * Prints You Chew score based on the rule 
       * that gives the highest score
       * If two rules give the same score, the rule that is 
       * alphabetically first description is used
       */
      if(seqLength == 5) {
         printf("You Chew score is %d: long sequence %d..%d.\n", 
                seqScore, min(array), max(array));  
      }          
      
      if(seqLength == 4 && ruleType == ONE_PAIR) { 
         if (onePairScore >= seqScore && onePairScore >= sum) {
            printf("You Chew score is %d: pair of %d's.\n", 
                   onePairScore, pair1Num); 
         } 
         else if (sum > onePairScore && sum > seqScore) {
            printf("You Chew score is %d: sum.\n", sum);
            }
         else if (seqScore > onePairScore && seqScore >= sum) {
            printf("You Chew score is %d: short sequence %d..%d.\n", 
                   seqScore, min(array), max(array));
         }          
      } 
      
      if(seqLength == 4 && ruleType != ONE_PAIR) {   

         /**
          * If the short sequence is type 1 
          * e.g 2 4 5 6 7,
          * The sequence starts from 4 and ends at 7
          */
         if (seq4 == 1) {
            printf("You Chew score is %d: short sequence %d..%d.\n", 
                   seqScore, secondSmallestNum, max(array));

         /**
          * If the short sequence is type 2 
          * e.g 2 3 4 5 7,
          * The sequence starts from 2 and ends at 5
          */
         } else if (seq4 == 2) {
            printf("You Chew score is %d: short sequence %d..%d.\n", 
                   seqScore, min(array), secondHighestNum);
         }
      }   
      
      if(seqLength != 4 && ruleType == ONE_PAIR) {      
         if (onePairScore >= sum) {
            printf("You Chew score is %d: pair of %d's.\n", 
                   onePairScore, pair1Num); 
         } else if (onePairScore < sum) {
            printf("You Chew score is %d: sum.\n", sum);  
         }
      } 
      
      if (ruleType == TWO_PAIRS) { 
         if (twoPairsScore >= sum) {
            printf("You Chew score is %d: pair of %d's and a pair of %d's\n"
                   ,twoPairsScore, pair2Num, pair1Num); 
         } else if (twoPairsScore < sum) {
            printf("You Chew score is %d: sum.\n", sum);  
         }      
      } 
      
      if (ruleType == TRIPLE) { 
         if (tripleScore > sum) {
            printf("You Chew score is %d: three %d's.\n", 
                   tripleScore, tripleNum); 
         } else if (tripleScore <= sum) {
            printf("You Chew score is %d: sum.\n", sum);  
         }           
      } 
      
      if (ruleType == FOURS) { 
         if (quadScore >= sum) {
            printf("You Chew score is %d: four %d's.\n", 
                   quadScore, quadNum); 
         } else if (quadScore < sum) {
            printf("You Chew score is %d: sum.\n", sum);  
         }         
      } 
      
      if (ruleType == FIVES) { ;
         if (fivesScore >= sum) {
            printf("You Chew score is %d: five %d's.\n", 
                   fivesScore, array[0]);
         } else if (fivesScore < sum) {
            printf("You Chew score is %d: sum.\n", sum);  
         }   
      } 
      
      if (ruleType == FULLHOUSE) { 
         if (fullhouseScore > sum) {
            printf("You Chew score is %d: three %d's and a pair of %d's\n"
                   , fullhouseScore, tripleNum, pair1Num); 
         } else if (fullhouseScore <= sum) {
            printf("You Chew score is %d: sum.\n", sum);  
         }
      }
      // If none of the rules apply, use sum rule
      if(ruleType == 0 && seqLength != 4 && seqLength != 5) {
         printf("You Chew score is %d: sum.\n", sum);   
      }
      
   } 
   
   return EXIT_SUCCESS;
   
}   

// Scans numbers into array  
int scanNumbers(int array[SIZE]) {  
   int fail = 0;
   int n = 0;
   while (n < SIZE && fail == 0) {   
      if (scanf("%d", &array[n]) != 1) {  // If it isn't a number,
         fail = 1;                        // program fails
      }  
      n++;  
   }
   if (fail == 1) {

      return EXIT_FAILURE;
   } 
      return EXIT_SUCCESS;   
   }


// Determine if there is an invalid input
int invalidInput(int n, int array[SIZE]) {
   if (n != EXIT_SUCCESS || array[0] < 1 || array[0] > 9
                         || array[1] < 1 || array[1] > 9
                         || array[2] < 1 || array[2] > 9
                         || array[3] < 1 || array[3] > 9
                         || array[4] < 1 || array[4] > 9) {

      printf("Invalid input: 5 integers 1..9 must be supplied.\n");
      
      return EXIT_FAILURE; 
   
   } else {

      return EXIT_SUCCESS; 
   }
}

/**
 * A counter array will hold a tally of the
 * amount of time each element occurs.
 * For instance, if the numbers scanned into the array are 1 2 2 4 5
 * The tally array is 0 1 2 0 1 1 0 0 0 0 
 */ 
void digitCount(int array[SIZE], int tally[SIZE_OF_TALLY]) {
     
    int i = 0;
    while (i < SIZE_OF_TALLY) {
        tally[i] = 0; // Sets every element in the tally to be zero
        i++;
    } 
    
    int tallyIndex = 0;
    int count = 0;
    while (count < SIZE) {
        tallyIndex = array[count]; 
        tally[tallyIndex] = tally[tallyIndex] + 1;
        count ++;
    }
}

// Gives the number of the first pair
int pair1Number (int tally[SIZE_OF_TALLY]) {
   int pair1;
   int i = 0;
   while (i < SIZE_OF_TALLY) {
      if (tally[i] == 2) {
         pair1 = i;
      }
      i++;
   } 

   return pair1;
}

// Gives the number of the second pair
int pair2Number (int tally[SIZE_OF_TALLY], int pair1Num) {
   int pair2;
   int i = 0;
   while (i < SIZE_OF_TALLY) {

      if (tally[i] == 2 && i != pair1Num) {
         pair2 = i;
      }
      i++;
   }

   return pair2;
}  

// Gives the number of the triplet
int tripleNumber(int tally[SIZE_OF_TALLY]) {
   int triple;
   int i = 0;
   while (i < SIZE_OF_TALLY) {
      if (tally[i] == 3) {
         triple = i;
      }
      i++;
   } 

   return triple;
}

// Gives the number of the 4 dice showing the same face
int quadNumber(int tally[SIZE_OF_TALLY]) {
   int quad;
   int i = 0;
   while (i < SIZE_OF_TALLY) {
      if (tally[i] == 4) {
         quad = i;
      }
      i++;
   } 

   return quad;
}

/**
 * Determines which rule to use
 * @return a global constant based on the rule used
 */
int whichRule (int tally[SIZE_OF_TALLY]) {
   int i, j, k;
   int fullhouse = 0;
   int twoPairs = 0;
   int triple = 0;
   int onePair = 0;

   int count = 0;
   while (count < SIZE_OF_TALLY) {
      if (tally[count] == 5) {   // If one of the numbers in the tally 
         return FIVES;           // is 5, use rule of fives
      }                          // e.g 0 0 0 0 5 0 0 0 0 0

      if (tally[count] == 4) {
         return FOURS;
      }
      
      if (tally[count] == 3) {    
         triple = 1;
         i = 0;
         while (i < SIZE_OF_TALLY) {
            if (tally[i] == 2) {
               fullhouse = 1;
            }
            i++;   
         }
      }
               
      if (tally[count] == 2) {
         onePair = 1;
         j = 0;   // Sets a new counter to find a new pair (if present)
         while (j < SIZE_OF_TALLY) {
            if (tally[j] == 2 && j != count) {
               twoPairs = 1;
            }
            j++;
         }
         
         k = 0;
         while (k < SIZE_OF_TALLY) {
            if (tally[k] == 3) {
               fullhouse = 1;
            }
         k++;
         }
      } 
      count ++; 
   }
   
   if (fullhouse == 1) {
      return FULLHOUSE;

   } else if (twoPairs == 1) {
      return TWO_PAIRS;  

   } else if (triple == 1) {
      return TRIPLE; 

   } else if (onePair == 1) {
      return ONE_PAIR; 

   }
   return EXIT_SUCCESS;
}

// Gives the total sum of all 5 numbers   
int sumScore(int array[SIZE]) {   
   int i = 0;
   int sum = 0;
   while (i < SIZE) {
      sum = sum + array[i];
      i++;
   }   
   
   return sum;
}

// Gives the score for 2 dice showing the same face   
int onePair(int tally[SIZE_OF_TALLY]) {
   int pair;
   int totalSum = 0;
   int i = 0;
   while (i < SIZE_OF_TALLY) {
      if (tally[i] == 2) {
         pair = i;
      }
      i++;
   } 
   totalSum = 14 + 2*pair; 

   return totalSum; 
}      

// Gives the score for 2 pairs    
int twoPairs(int pair1Num, int pair2Num) {
   int totalSum;
    
   totalSum = 13 + (2*pair1Num) + (2*pair2Num);  
   return totalSum; 
  
}      

// Gives the score for 3 dice showing the same face       
int triple(int tally[SIZE_OF_TALLY]) {
   int tripleNumber;
   int totalSum = 0;
   int i = 0;
   while (i < SIZE_OF_TALLY) {
      if (tally[i] == 3) {
         tripleNumber = i;
      }
      i++;
   } 
   totalSum = 15 + 3*tripleNumber;  

   return totalSum; 
}      

// Gives the score for 4 dice show the same face   
int quad(int tally[SIZE_OF_TALLY]) {
   int quadNumber;
   int totalSum = 0;
   int i = 0;
   while (i < SIZE_OF_TALLY) {
      if (tally[i] == 4) {
         quadNumber = i;
      }
      i++;
   } 
   totalSum = 16 + 4*quadNumber;  

   return totalSum; 
}    
 
// Gives the score for 3 dice showing the same face 
// and another 2 dice showing the same face
int fullhouse(int tally[SIZE_OF_TALLY]) {
   int pair, triple;
   int totalSum = 0;
   int i = 0;
   while (i < SIZE_OF_TALLY) {
      if (tally[i] == 2) {
         pair = i;
      } 
      if (tally[i] == 3) {
         triple = i;
      }
      i++;    
   }
   totalSum = 15 + 3*triple + 2*pair;  

   return totalSum; 
}
 
/**
 * Finds the longest sequence of numbers in an array
 * @return the length of the longest sequence
 */ 
int longestSeq(int array[SIZE]){
  
   int low = min(array);
   int high = max(array);
   int seqTally[high - low + 1];

   // Tally up our array
   count(array, low, high, seqTally);

   int maxSeqLength = 0;  // Max seq length so far
   int seq = 0;  // Current seq length
   int i = 0;
   while (i < high - low + 1) { // hi - lo + 1 is the size of counter
      if(seqTally[i] > 0){
         // Non-zero so increment current sequence length
         seq++;
      } else {
         // Reset the counter if we find a zero
         seq = 0;
      }

      // If the current seq length exceeds max then update max
      if(seq > maxSeqLength){
      	maxSeqLength = seq;
      }
      i++;
   }

   return maxSeqLength;
}

/**
 * Counts the number of times each element in an array occurs.
 * 
 * Finds the maximum and minimum elements
 * in the array and then offset all of the lookups
 * by '-min' to get it in the range 0..max-min. 
 * Therefore the size of counter will be max - min + 1
 */

void count(int array[SIZE], int min, int max, int seqTally[]){
   // A bunch of preconditions which must all be true
   assert(min > 0);
   assert(max > 0);
   assert(min <= max);

   // Initialize the counter array
   int i = 0;
   while(i < max - min + 1) {
      seqTally[i] = 0;
      i++;
   }
   // Count the numbers
   i = 0;
   while(i < SIZE){
      seqTally[array[i] - min]++;
      i++;
   }
}

// Finds the maximum number in the array
int max(int array[SIZE]){

   int max = array[0];
   int i = 1;
   while (i < SIZE) {
      if(array[i] > max) {
         max = array[i];
      }
      i++;
   }

   return max;
}

// Finds the second largest number in the array
int secondMax(int array[SIZE]){
   
   int secMax = 0;
   int max = 0;
   int i = 0; 
   while(i < SIZE){
   	/* If current element is bigger than min 
	    * then update both min and secMax. 
	    */
      if (array[i] > max) {
         secMax = max;
         max = array[i];
      /* If array[i] is in between max and secMax 
       * then update secMax  
       */      
      } else if (array[i] > secMax && array[i] != max) {
         secMax = array[i];
      }
      i++;
   }

   return secMax;       
}

// Finds the smallest number in the array
int min(int array[SIZE]){

   int min = array[0];
   int i = 1;
   while(i < SIZE){
      if(array[i] < min){
         min = array[i];
      }
      i++;
   }

  return min;
}

// Finds the second smallest number in the array
int secondMin(int array[SIZE]){
   
   int smallest, secondSmallest;
	if (array[0] < array[1]) {
	    smallest = array[0];
	    secondSmallest = array[1];
	} else {
	    smallest = array[1];
	    secondSmallest = array[0];
	}

	int i = 2;
	while(i < SIZE) {
	   if (array[i] < smallest) {
	        secondSmallest = smallest;
	        smallest = array[i];
	   } else if (array[i] < secondSmallest) {
	        secondSmallest = array[i];
  		}
  		i++;
  	}
  	return secondSmallest;
}

/* Determine the type of short sequence
 * If the numbers are 2 5 6 7 8, the tally is 0 1 0 0 1 1 1 1 0.
 * The min number (2) is not in the sequence, hence it is type 1  
 *
 * If the numbers are 2 3 4 5 9, the tally is 0 1 1 1 1 0 0 0 1.
 * The min number (2) is in the sequence, hence it is type 2.
 *
 */
int seq4Type(int min, int tally[SIZE_OF_TALLY]){

	int i = 1;
	while (i < SIZE_OF_TALLY) {
		if(tally[i] == 1 && i == min &&
		   tally[i-1] == 0 && tally [i+1] == 0 ) {
		   // Type 1
			return 1;
		}
		i++;
	}
	// Type 2
	return 2;
}


// Finds the sum based on the sequence length
int seqSum (int seqLength, int ruleType, int seq4Type,
            int secondHighestNum, int max) {
   
   int seq4, seq5;
   /**
    * If there is a pair in the numbers e.g 1 1 2 3 4, 
    * it is a short sequence from 1..4,
    * hence the highest face in the sequence is 4 (the max)
    * 
    * However, if there is no pair in the numbers e.g 1 2 3 4 8
    * it is a short sequence from 1..4
    * but the highest face in the sequence is the 
    * second largest number in the array
    */
   if (seqLength == 4 && ruleType == ONE_PAIR) {
      seq4 = 25 + max;

      return seq4;

   } else if (seqLength == 4 && ruleType == 0) {
      // Depends on the type of short sequence
      if (seq4Type == 1) {
         seq4 = 25 + max;
         return seq4;
         
      }
      if (seq4Type == 2) {
         seq4 = 25 + secondHighestNum;
         return seq4;
      
      }
   }
         
   if (seqLength == 5) {
      seq5 = 37 + max;

      return seq5;
   }  
   return EXIT_SUCCESS;  
} 





