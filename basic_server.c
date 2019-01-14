#include "pipe_networking.h"
#include "game.c"
#include "setup.c"
#include "files.c"

void play(char * buf, int vals[], int locations[], int place[])
{
  int positions[3]; //stores the cards the user chose
  
  if(strcmp(buf, "r") && strcmp(buf, "h")) //r for refresh and h for help
    {
      if (input_to_board_positions(buf, positions)) //storing the positions on the board of the user's input
	{
	  //strcat(buf, " yes, that's an input. gg.\n");
	  if(set_check(vals[ locations[ positions[0] ] ],
		       vals[ locations[ positions[1] ] ],
		       vals[ locations[ positions[2] ] ])) //check if user input is a valid set

	    {
	      //if(write_line(place, locations, 1)) //check if the other player found a set
	      //{
	      strcpy(buf, "You found a set! Good job! Plus one point.\n"); 
	      replace(locations, place, positions); //put new cards in the display
	      //}
	      //else
	      //strcpy(buf, "The other player beat you to it!\n");
	    }
	  else
	    strcpy(buf, "No, that wasn't a set. Try again.\n");
	}
      else
	strcpy(buf, "That wasn't a valid input, bro.\n"); //wrong number of letters, etc
    }
  else if(!strcmp(buf, "h")) //help
    strcpy(buf, "Enter three letters on the keyboard corresponding to the position of each card on the board as follows (no spaces):\nq w e r [t]\na s d f [g]\nz x c v [b]\n");
  else 
    strcpy(buf, "Refreshed.\n"); //refresh
  print_twelve(locations, vals, buf); //add the cards
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

  
  char * buf = malloc(2048 * sizeof(char));
  from_client = server_handshake( &to_client );
  swap(deck);
  deal_initial(locations);

  //write_line(place, locations, 0); //initialize shared memory
  //perror("error writing");
  
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

