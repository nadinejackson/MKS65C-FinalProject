#include "pipe_networking.h"
#include "game.c"
#include "setup.c"
#include "files.c"

void play(char * buf, int vals[], int locations[], int place[])
{
  int positions[3];
  char temp[10];
  if(strcmp(buf, "r") && strcmp(buf, "h"))
    {
      if (input_to_board_positions(buf, positions))
	{
	  //strcat(buf, " yes, that's an input. gg.\n");
	  if(set_check(vals[ locations[ positions[0] ] ],
		       vals[ locations[ positions[1] ] ],
		       vals[ locations[ positions[2] ] ]))

	    {
	      //if(write_line(place, locations, 1))
	      //{
		  strcpy(buf, "You found a set! Good job! Plus one point.\n");
		  replace(locations, place, positions);
		  //}
		  //else
		//strcpy(buf, "The other player beat you to it!\n");
	    }
	  else
	    strcpy(buf, "No, that wasn't a set. bg.\n");
	}
      else
	strcpy(buf, "That wasn't a valid input, bro.\n");
    }
  else if(!strcmp(buf, "h"))
    strcpy(buf, "Enter three letters on the keyboard corresponding to the position of each card on the board as follows (no spaces):\nq w e r [t]\na s d f [g]\nz x c v [b]\n");
  else 
    strcpy(buf, "Refreshed.\n");
  print_twelve(locations, vals, buf);
}
int main()
{
  int locations[15];
  create();//create shared memory to store locations
  
  int deck[81];
  int pid = getpid();
  int to_client;
  int from_client;
  int place[1];
  place[0] = 12;

  write_line(place, locations, 0);
  //perror("error writing");
  
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

