#include "pipe_networking.h"
#include "game.c"

int play(char * buf, char * response, int locations[], int vals[], int * undealt)
{
  int * chosen = malloc(3 * sizeof(int));
  if(letters_to_vals(buf, locations, vals, chosen))
    {
      if (is_set(chosen))
	{
	  strcpy(response, "ya u did it");
	  replace(vals, locations, chosen, undealt);
	}
      else
	strcpy(response, "na, try again");
    }
  else
    strcpy(response, "error");
}
int main() {
  
  int locations[15];
  int vals[81];
  int * undealt = 0;
  int pid = getpid();
  int to_client;
  int from_client;
  char * buf = malloc(1024 * sizeof(char));
  char * response = malloc(1024 * sizeof(char));
  from_client = server_handshake( &to_client );

  swap(vals); //initial swap
  deal_initial(vals, locations, undealt);
  display(vals, locations);
  while(1)
    {
      if (getpid() - pid)
	{
	  if (read(from_client, buf, 1024 * sizeof(char)))
	    {
	      perror("error");
	      printf("received %s\n", buf);
	      play(buf, response, locations, vals, undealt);
	      write(to_client, response, 1024 * sizeof(char));
	    }
	  else
	    printf("goodbye");
	    exit(0);
	}
      else
	from_client = server_handshake( &to_client );
    }
}
