#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>


void swap(int vals[81]) //initialize arrays to values 0-80 in random order
{
  int c = 81;
  while(c--)
    vals[c] = c; //populate with values in order
  //randomly swap until deck is randomized
}
int * letters_to_vals(char * input, int locations[], int vals[], int * chosen)
{
  if (strlen(input) != 3)
    return NULL;
  int c = 3;
  int n;
  while (c)
    {
      chosen[c] = c;
    }
  return chosen;
}
int is_set(int chosen[])
{
  return 1;
}
void replace(int vals[], int locations[], int chosen[], int * undealt)
{
}
char * display(int vals[], int locations[])
{
  char * placeholder = "the cards go here[]\n";
  return placeholder;
}
void deal_initial(int vals[], int locations[], int * undealt)
{
  *undealt = 12;
}
