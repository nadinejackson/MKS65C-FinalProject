
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

char * KEYBOARD = "qwerasdfzxcvtgb";
//int positions[3];
char board[100];

int input_to_board_positions (char * input, int positions[]) {
  if ( strlen(input) != 3 || input[0] == input[1]) {
      //printf("Invalid input! A set must be of 3 cards.\n");
        return 0;
    }

    for ( int i=0 ; i<3 ; i++ ) { // for every position
        char letterInInput[2];
        strncpy(letterInInput, input + i, 1);
        
        char * letterInKeyboard = strstr( KEYBOARD, letterInInput );
        if (letterInKeyboard != NULL) { // match
            int position = letterInKeyboard-KEYBOARD;
            positions[i] = position;
        }
        else { // no match found
	  //printf("A letter in the input is not within the board!\n");
            return 0;
        }
        
    }
    // done finding all matches
    //printf("positions: |%d|%d|%d|\n", positions[0], positions[1], positions[2]);
    return 1;
}

int set_check_helper (int a, int b, int c) {
  printf("%d %d %d\n", a, b, c);
  if (a == b && b == c) // therefore a=c=b
        return 1; // true
    else if ( a!=b && b!=c && a!=c ) //all different
        return 1;
    else
        return 0;
}

int set_check (int a, int b, int c) {
    int attributes[4];

    int i;
    for( i=0 ; i<4 ; i++ ) {
        attributes[i] = set_check_helper(a%3, b%3, c%3);
        a /= 3;
        b /= 3;
        c /= 3;
    }

    for( i=0 ; i<4 ; i++ ) {
        if ( attributes[i] == 0 )
            return 0;
    }
    
    return 1;
}

void print_twelve (int * locations , int * values, char * buf) {

    char temp[100];

    int nums[12];
    int i, j;
    for ( i=0 ; i<3 ; i++ ) {
        for ( j=0 ; j<4 ; j++ ) {
            sprintf( temp, "%d\t", values[ locations[4*i+j] ] );
            strcat(buf, temp);
            nums[4*i + j] = values[locations[4*i+j]];
        }
        strcat(buf, "\n");
    }
    //strcat(buf, " _   _   _   _ \n");
    int a,b,c,d;
    
    for(a = 0; a < 3; a++)
      {
      for(b = 0; b < 3; b++)
	{
	  for(c = 0; c < 4; c++)
	    {
	      //card edges
	      strcat(buf, "|");

	      d = nums[4 * a + c];

	      //colors
	      if (d % 3 == 0)
		sprintf(temp, "%c[32m", (char) 27);
	      else if ( d % 3 == 1)
		sprintf(temp, "%c[31m", (char) 27);
	      else
		sprintf(temp, "%c[35m", (char) 27);
	      strcat(buf, temp);

	      d /= 3;
	      
	      //shape
	      if (d % 3 == 0)
		strcat(buf, "O");		
	      else if ( d % 3 == 1)
		strcat(buf, "^");
	      else
		strcat(buf, "~");
	    
	      //card edges (white)
	      sprintf(temp, "%c[37m", (char) 27);
	      strcat(buf, temp);
	      strcat(buf, "| ");
	    }
	  strcat(buf, "\n");
	}
      strcat(buf, "\n");
      }
    //strcat(buf, " -  -  -  - \n");
}

char * print_fifteen (int * locations , int * values) {

    char temp[100];
    strcpy(board, "");
    
    int i, j;
    for ( i=0 ; i<3 ; i++ ) {
        for ( j=0 ; j<5 ; j++ ) {
            sprintf( temp, "%d\t", values[ locations[5*i+j] ] );
            strcat(board, temp);
            
        }
        strcat(board, "\n");
    }

    return board;
}

void replace (int * locations , int * placemarker , int * positionToReplace ) {
    int i;
    for ( i=0 ; i<3 ; i++ ) {
        locations[ positionToReplace[i] ] = *placemarker; //not values[placemarker]
        (*placemarker)++;
    }
}

void plus_three ( int * locations , int * placemarker ) {
    int i;
    for ( i=0 ; i<3 ; i++ ) {
        locations[12+i] = *placemarker; //not values[placemarker]
        placemarker++;
    }
    
}

void deal_initial(int * locations)
{
  int i = 15;
  while(i--)
    locations[i] = i;
}

void swap(int vals[])
{
  int c = 81;
  while(c--)
    vals[c] = c;
  srand(time(NULL));
  int r;
  int i;
  c = 81;
  while(c)
    {
      i = rand() % 81;
      r = vals[c % 81];
      vals[c % 81] = vals[i];
      vals[i] = r;
      c--;
    }
}
void swap_test(int vals[])
{
  int c = 81;
  while(c--)
    vals[c] = c;
}


//int main() {
    /* char * q = "QWE"; */
    /* char * r = "WER";   */
    /* char * m = "WRS"; */
    /* char * o = "CVT"; */
    /* char * w = "CVB"; */
    /* char * e = "RTY"; */

    /* int * x = input_to_board_positions(q); //0 1 2 */
    /* int * y = input_to_board_positions(r); //1 2 3 */
    /* int * d = input_to_board_positions(m); //1 3 5 */
    /* int * p = input_to_board_positions(o); //10 11 12 */
    /* int * z = input_to_board_positions(w); //10 11 14 */
    /* int * t = input_to_board_positions(e); //3 12 --> NULL */

    /* set_check_helper(0, 2, 1); */
    /* set_check_helper(0, 0, 0); */
    /* set_check_helper(1, 0, 2); */
    /* set_check_helper(0, 1, 1); */

    /* set_check( 36, 29, 46 ); //1 */
    /* set_check( 39, 52, 23 ); //0 */

    /* int loc[12] = {0,1,2,3,4,5,6,7,8,9,10,11}; */
    /* int val[12] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; */


    /* printf("%s\n", print_twelve(loc, val)); */

    /* int loc2[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14}; */
    /* int val2[15] = {14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; */


    /* printf("%s\n", print_fifteen(loc2, val2)); */
    
//}
