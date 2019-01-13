#include "pipe_networking.h"
#include "game.c"
void play(char * buf, int vals[], int locations[])
{
  char temp[10];
  strcat(buf, " yes, this is working.\ncards:\n");
  /*  int i;
 for (i = 0; i < 12; i++)
    {
      sprintf(temp, "[%d]\n", vals[locations[i]]);
      strcat(buf, temp);
      printf("[%d]\n", vals[locations[i]]);
      }*/
  print_twelve(locations, vals, buf);
}
int main()
{
  int locations[15];
  int deck[81];
  int pid = getpid();
  int to_client;
  int from_client;
  int place[1];
  place[0] = 12;
  char * buf = malloc(1024 * sizeof(char));
  from_client = server_handshake( &to_client );
  swap(deck);
  deal_initial(locations);
  while(1)
    {
      if (getpid() - pid)
	{
	  if (read(from_client, buf, 1024 * sizeof(char)))
	    {
	      play(buf, deck, locations);
	      write(to_client, buf, 1024 * sizeof(char));
	    }
	  else
	    exit(0);
	}
      else
	from_client = server_handshake( &to_client );
    }
}

