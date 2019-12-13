/**
 * Author      : Pua Qie Shang
 * Project     : CWords
 * This program is to see words that be created from the letters given
 * in a way to maximise the score. Happy playing! :)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_TILES 25
#define BOARD_SIZE 5
#define MAX_WORDS 5000
#define WORD_SIZE_3 3
#define WORD_SIZE_4 4
#define WORD_SIZE_5 5

struct tile {
   char letter;
   int score; 
};

typedef struct tile Tile;

int readLetter(Tile *t);
int readScore (Tile *t);
int checkTileScore(Tile t[]);
void uppercaseToLowercase (Tile *t);
void printTile(Tile t[]);
void printBoard(Tile b[][BOARD_SIZE]);
void storeWords(FILE *words3, FILE *words4, FILE *words5, 
                char list3[][WORD_SIZE_3+2],char list4[][WORD_SIZE_4+2], 
                char list5[][WORD_SIZE_5+2], 
                int *numRows3, int *numRows4, int *numRows5);
// Both 'char (*list)[size]' and char list[][size] are the same
int checkRow   (int maxListRows, int counter, int size, 
               char list[][size+2], Tile b[][BOARD_SIZE], int boardRow);                
int checkCol   (int maxListRows, int counter, int size, 
               char list[][size+2], Tile b[][BOARD_SIZE], int boardCol);  
int findWords3 (int maxListRows, int size, char list[][size+2], 
               Tile b[][BOARD_SIZE]);    
int findWords4 (int maxListRows, int size, char list[][size+2], 
               Tile b[][BOARD_SIZE]);       
int findWords5 (int maxListRows, int size, char list[][size+2], 
               Tile b[][BOARD_SIZE]);  
void finalTile (Tile b[][BOARD_SIZE]);
              
int main (int argc, char*argv[]) {
   
   Tile t[NUM_TILES];    
   Tile b[BOARD_SIZE][BOARD_SIZE]; // Board

   printf("Enter 25 tiles: ");
   
   int i = 0;
   while (i < NUM_TILES) {       
      
      if (readLetter(&t[i]) == EXIT_FAILURE || 
          readScore(&t[i]) == EXIT_FAILURE) {
         fprintf(stderr,"Error in input\n");
         return EXIT_FAILURE;       
      }     
      i ++;                 
   }

   int validTest2 = checkTileScore(t);
   
   if(validTest2 == EXIT_FAILURE) {
      fprintf(stderr,"Error in input\n");
      return EXIT_FAILURE;
   }
   
   i = 0;
   while (i < NUM_TILES) {      
      uppercaseToLowercase(&t[i]);
      i ++;  
   }

   printTile(t);

   printf("\nEnter row and column for each tile ...\n");  
   
   int j;
   i = 0;
   while (i < BOARD_SIZE) {
      j = 0;
      while (j < BOARD_SIZE) {
         (b[i][j].letter) = '.';
         (b[i][j].score) = '.';
         j++;
      }
      i++;
   }
   
   int turn = 0;
   int allOccupied = 0;
   int check;
   
   // Monitors each turn
   while (allOccupied != 1) {
   
      int row, col;
      
      printf("Tile #%d: %c/%d? ",(turn+1),t[turn].letter,t[turn].score);
      int validInput = scanf("%d %d\n", &row, &col);
      
      if(validInput != 2 || row < 0 || row >= BOARD_SIZE || 
         col < 0 || col >= BOARD_SIZE) {
         fprintf(stderr,"Error in input\n");
         return EXIT_FAILURE;      
      }
       
      if (b[row][col].letter == '.' && b[row][col].score == '.') {
       
         b[row][col].letter = t[turn].letter;
         b[row][col].score = t[turn].score + '0';
         turn++; // For the next trial
         printBoard(b);
      }
      
      if (turn == NUM_TILES) {
         allOccupied = 1;
      }
   }

   
   FILE *words3 = fopen("words3.txt", "r");
   FILE *words4 = fopen("words4.txt", "r");
   FILE *words5 = fopen("words5.txt", "r");
 
   if (words3 == NULL || words4 == NULL || words5 == NULL) {
        fprintf(stderr,"Error: File cannot be opened\n");
        return EXIT_FAILURE;
   }   
   
   /*
    * The column index of the lists are added by 2 
    * to include '\n' and '\0'
    */
   char list3[MAX_WORDS][WORD_SIZE_3 +2];
   char list4[MAX_WORDS][WORD_SIZE_4 +2];
   char list5[MAX_WORDS][WORD_SIZE_5 +2];   
   
   int numRows3, numRows4, numRows5;
    
   storeWords(words3, words4, words5, list3, list4, list5, 
              &numRows3, &numRows4, &numRows5);
   
   printf("Words: \n"); 
   
   int sum3 = findWords3(numRows3, WORD_SIZE_3, list3, b);
   printf("Words of length 3 = %d\n", sum3);
   
   int sum4 = findWords4(numRows4, WORD_SIZE_4, list4, b);
   printf("Words of length 4 = %d\n", sum4); 

   int sum5 = findWords5(numRows5, WORD_SIZE_5, list5, b);
   printf("Words of length 5 = %d\n", sum5);
   
   printf("\nTOTAL = %d\n", sum3 + sum4 + sum5);
   
   finalTile(b);
      
   return EXIT_SUCCESS;

}

int readLetter(Tile *t) {  

   char c;
   int score = 0;      
    
   if ((c = getchar()) != EOF) {
      
      while (isspace(c) && c != EOF) {
         c = getchar();
      }

      if(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
         (t->letter) = c;
      
         return EXIT_SUCCESS; // successfully read in an alphabet
      }
               
   }
   return EXIT_FAILURE; // read in a non-letter, hence fails
}      

int readScore(Tile *t) { 
   
   if (scanf("%d", &t->score) == 1) {
      return EXIT_SUCCESS;
   }
   
   return EXIT_FAILURE; // read in a non-letter, hence fails
}      

// Ensure tile scores are within 0 to 100, if not returns 0
int checkTileScore(Tile t[]) {

   int i = 0;
   while (i < NUM_TILES) {
   
      if (t[i].score < 0 || t[i].score > 100) {      
         return EXIT_FAILURE; 
      }
      i++;
   }
   return EXIT_SUCCESS; 
}

void uppercaseToLowercase (Tile *t) {
      
   if ((t->letter) >= 'A' && (t->letter) <= 'Z') {
      int position = (t->letter) - 'A';
      (t->letter) = position + 'a';
   }
           
} 

void printTile(Tile t[]){
   
   printf("Tiles: ");
   int n = 0;
   while (n < NUM_TILES) {
      printf("%c/%d ", (t[n].letter), (t[n].score));
      n++;
   }
   printf("\n");
}

void printBoard(Tile b[][BOARD_SIZE]) {
   
   printf("   ");

   int i, j;
   int count = 0;
   j = 0;
   while ( j < BOARD_SIZE ) {
     printf(" %d  ", j);
     j++;
   }
   printf("\n");
    
   i = 0;
   while (i < BOARD_SIZE) {
      printf("%d: ", i);
        
      j = 0;
      while (j < BOARD_SIZE) {
      
         printf("%c/%c ",(b[i][j].letter),(b[i][j].score));         
         
         j++;
      }
      printf("\n");
      i++;       
    }
    printf("\n");
}

// Stores the 3, 4, and 5 letter words into an array of strings
void storeWords(FILE *words3, FILE *words4, FILE *words5, 
                char list3[][5],char list4[][6], char list5[][7],
                int *numRows3, int *numRows4, int *numRows5) {
                
    // Array size is 5 because have to include word size , '\n' and '\0'
    char eof3[5]; 
    
    int lineNum  = 0;
    while(fgets(eof3, MAX_WORDS, words3) != NULL) {
           
         // Copies the words3.txt to destination (eof)
         strcpy(list3[lineNum], eof3);    
         lineNum++;   
    } 
     
    /* *
     * Initiliaze a pointer to indicate the max rows 
     * containing strings in list3[][]  
     */
    *numRows3  = lineNum;
    
    char eof4[6];
    lineNum  = 0;
    while(fgets(eof4, MAX_WORDS, words4) != NULL) {

         strcpy(list4[lineNum], eof4);       
         lineNum++;   
    }
    *numRows4 = lineNum;
    
    char eof5[7];
    lineNum  = 0;
    while(fgets(eof5, MAX_WORDS, words5) != NULL) {
      
         strcpy(list5[lineNum], eof5);         
         lineNum++;   
    }
    *numRows5 = lineNum;
    
   fclose(words3.txt);
   fclose(words4.txt);
   fclose(words5.txt);

}

/**
 * This function compares list3 with the characters on the board 
 * by row and column
 *
 * To find Words with 3 letters, the counter should start from
 * 0, 1, 2. This is to find multiple words that might be on the 
 * same row/column. For instance, consider this row:
 *
 *  0  1  2  3  4
 *  e  a  t  i  n
 * 
 * So 'eat' can be found when counter starts from 0, 
 * whereas 'tin' can be found when counter starts from 2.
 */
int findWords3(int maxListRows, int size, char list3[][size+2],
               Tile b[][BOARD_SIZE]) {
   
   int rowScore = 0;
   int colScore = 0;
   int totalSco = 0;
   
   int counter = 0;
   int boardRow = 0;
   int boardCol = 0;
   while (boardRow < BOARD_SIZE) {
      
      counter = 0;
      while (counter < 3){
         rowScore = rowScore + checkRow(maxListRows,counter, WORD_SIZE_3,
                                        list3, b, boardRow);      
         counter++;
      }
      boardRow ++;      
   }

   counter = 0;
   while (boardCol < BOARD_SIZE) {
      counter = 0;
      while (counter < 3){
         colScore = colScore + checkCol(maxListRows, counter, WORD_SIZE_3, 
                                       list3, b, boardCol);     
         counter++;
      }     
      boardCol ++;
   }
   
   totalSco = colScore + rowScore;

   return totalSco;
}

// Finds word with 4 letters
int findWords4(int maxListRows, int size, char list4[][size+2], 
               Tile b[][BOARD_SIZE]) {
   
   int rowScore = 0;
   int colScore = 0;
   int totalSco = 0;
   
   int counter = 0;
   int boardRow = 0;
   int boardCol = 0;
   
   while (boardRow < BOARD_SIZE) {
      counter = 0;
      while (counter < 2){
         rowScore = rowScore+checkRow(maxListRows, counter, WORD_SIZE_4,
                                      list4, b, boardRow);      
         counter++;
      }
      boardRow ++;
      
   }

   counter = 0;
   while (boardCol < BOARD_SIZE) {
   
      counter = 0;
      while (counter < 2){
         colScore = colScore+checkCol(maxListRows, counter, WORD_SIZE_4,
                                      list4, b, boardCol);     
         counter++;
      }
      
      boardCol ++;
   }
   
   totalSco = colScore + rowScore;

   return totalSco;
}

// Find words with 5 letters
int findWords5(int maxListRows, int size, char list5[][size+2], 
               Tile b[][BOARD_SIZE]) {
   
   int rowScore = 0;
   int colScore = 0;
   int totalSco = 0;
   
   int counter = 0;
   int boardRow = 0;
   int boardCol = 0;

   while (boardRow < BOARD_SIZE) {
      
      rowScore = rowScore + checkRow(maxListRows, counter, WORD_SIZE_5, 
                                     list5, b, boardRow);            
      boardRow ++;     
   }

   counter = 0;
   while (boardCol < BOARD_SIZE) {
     
      colScore = colScore + checkCol(maxListRows, counter, WORD_SIZE_5, 
                                     list5, b, boardCol);           
      boardCol ++;
   }
   
   totalSco = colScore + rowScore;
    
   return totalSco;
}

/**
 * For the header file, why can't I just use char list[][size] instead, 
 * is it because its incompatible?
 *
 * Anyways, this function is to compare the words in the list and 
 * the words in the board for a row.
 */ 
int checkRow (int maxListRows, int counter, int size, 
              char list[][size+2],Tile b[][BOARD_SIZE], int boardRow) {

   int listRow, listCol, boardCol;
   int same;
   int rowSco = 0;
   int totalRowSco = 0;
   int scoreCounter,charCounter;
   
   //listCol = 0;
   listRow = 0;
   while (listRow < maxListRows) {
      
      same = 0;
      listCol = 0;
      boardCol = counter;
         
     
      while (listCol < size && boardCol < size+counter) {
          
         if(list[listRow][listCol] == b[boardRow][boardCol].letter) {    
            same ++;
               
            if (same == size) {               
               
               scoreCounter = counter;
               //printf("hello\n");                 
               rowSco = 0;
               while (scoreCounter < size+counter) {
                  rowSco = rowSco + (b[boardRow][scoreCounter] .score -'0');           
                  scoreCounter++;       
               } 
               totalRowSco = totalRowSco + rowSco;            
                  
               charCounter = 0;
               while (charCounter < size) {
                  printf("%c", list[listRow][charCounter]);
                  charCounter++;
               }          
                  printf(" = %d\n", rowSco);                 
               }       
         }
         listCol++;
         boardCol++;
      }            
      listRow++;
      //listCol = 0;  
   }
   return totalRowSco; 
}  


int checkCol (int maxListRows, int counter, int size, 
              char list[][size+2], Tile b[][BOARD_SIZE], int boardCol) { 

   int listCol, listRow, boardRow;
   int same;
   int colSco = 0;
   int totalColSco = 0;
   int scoreCounter,charCounter;
   
   //listCol = 0;
   listRow = 0;
   while (listRow < maxListRows) {
          
      same = 0;
      listCol = 0;
      boardRow = counter;
      while (listCol < size && boardRow < size+counter) {
          
         if(list[listRow][listCol] == b[boardRow][boardCol].letter) {     
            
            same ++;
               
            if (same == size) {
                         
               scoreCounter = counter;
               colSco = 0;
               while (scoreCounter < size+counter) {
                  colSco = colSco + (b[scoreCounter][boardCol].score -'0');           
                  scoreCounter++;       
               }   
                    
               totalColSco = totalColSco + colSco;       
                  
               charCounter = 0;
               while (charCounter < size) {
                  printf("%c", list[listRow][charCounter]);
                  charCounter++;
               }
               printf(" = %d\n", colSco);
            }             
         }             
         listCol++;         
         boardRow++;
      }          
      listRow++;  
   }

   return totalColSco;
}

// Print a list of letter/value pairs from left-to-right and 
// top-to-bottom representing the final state of the game board.
void finalTile (Tile b[][BOARD_SIZE]) {
   int i, j;
   
   i = 0;
   while (i < BOARD_SIZE) {
      j = 0;
      while (j < BOARD_SIZE) {
         
         printf("%c %c ", b[i][j].letter, b[i][j].score );     
         j++;
      }
      i++;
   }
   printf("\n");
}








