#include <stdio.h>
#include <string.h>

char * KEYBOARD = "QWERASDFZXCVTGB";
int positions[3];
char board[100];

int * input_to_board_positions (char * input) {
    if ( strlen(input) != 3 ) {
        printf("Invalid input! A set must be of 3 cards.\n");
        return NULL;
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
            printf("A letter in the input is not within the board!\n");
            return NULL;
        }
        
    }
    // done finding all matches
    printf("|%d|%d|%d|\n", positions[0], positions[1], positions[2]);

    return positions;
}

int set_check_helper (int a, int b, int c) {
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

char * print_twelve (int * locations , int * values) {

    char temp[100];
    strcpy(board, "");

    int i, j;
    for ( i=0 ; i<3 ; i++ ) {
        for ( j=0 ; j<4 ; j++ ) {
            sprintf( temp, "%d\t", values[ locations[4*i+j] ] );
            strcat(board, temp);
            
        }
        strcat(board, "\n");
    }

    return board;
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
        locations[ positionToReplace[i] ] = placemarker; //not values[placemarker]
        placemarker++;
    }
}

void plusThree ( int * locations , int * placemarker ) {
    int i;
    for ( i=0 ; i<3 ; i++ ) {
        locations[12+i] = placemarker; //not values[placemarker]
        placemarker++;
    }
    
}


int main() {
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
    
}
