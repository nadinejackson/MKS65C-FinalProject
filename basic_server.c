#include "pipe_networking.h"
#include "game.c"
void play(char * buf, int vals[], int locations[], int place[])
{
  int positions[3];
  char temp[10];
  if (input_to_board_positions(buf, positions))
    {
      //strcat(buf, " yes, that's an input. gg.\n");
      if(set_check(vals[ locations[ positions[0] ] ],
		   vals[ locations[ positions[1] ] ],
		   vals[ locations[ positions[2] ] ]))

	{
	  strcat(buf, " yes, that's a set. gg.\n");
	  replace(locations, place, positions);
	}
      else
	strcat(buf, " no, that wasn't a set. bg.\n");
    }
  else
    strcat(buf, " that wasn't an input, bro.\n");
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
  char * buf = malloc(2048 * sizeof(char));
  from_client = server_handshake( &to_client );
  swap(deck);
  int i;
  //for(i = 0; i < 81; i++)
  //printf("[%d]\n", deck[i]);
  deal_initial(locations);
  while(1)
    {
      if (getpid() - pid)
	{
	  if (read(from_client, buf, 1024 * sizeof(char)))
	    {
	      play(buf, deck, locations, place);
	      write(to_client, buf, 1024 * sizeof(char));
	    }
	  else
	    exit(0);
	}
      else
	from_client = server_handshake( &to_client );
    }
}

