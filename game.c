#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

void swap(int vals[]) //initialize arrays to values 0-80 in random order
{
  
  //printf("the swap fxn has started\n");
  int c = 81;
  while(c--)
    vals[c] = c; //populate with values in order
  srand(time(NULL));
  int r;
  int i;
  c = 81;
  //printf("about to loop, %d\n", c);
  while(c)
    {
      //printf("hello is anyone here? %d\n", c);
      i = rand() % 81;
      r = vals[c % 81];
      vals[c % 81] = vals[i];
      //vals[i] = r;
      c--;
    }
  //printf("it yeeted for some reason\n");
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
