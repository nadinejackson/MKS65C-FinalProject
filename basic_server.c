#include "pipe_networking.h"
#include "game.c"
void play(char * buf, int vals[])
{
  char temp[10];
  strcat(buf, " yes, this is working.\n");
  int i;
  for (i = 0; i < 81; i++)
    {
      sprintf(temp, "[%d]\n", vals[i]);
      strcat(buf, temp);
      printf("[%d]\n", vals[i]);
    }
}
int main()
{
  int deck[81];
  int pid = getpid();
  int to_client;
  int from_client;
  char * buf = malloc(1024 * sizeof(char));
  from_client = server_handshake( &to_client );
  while(1)
    {
      if (getpid() - pid)
	{
	  if (read(from_client, buf, 1024 * sizeof(char)))
	    {
	      swap(deck);
	      play(buf, deck);
	      write(to_client, buf, 1024 * sizeof(char));
	    }
	  else
	    exit(0);
	}
      else
	from_client = server_handshake( &to_client );
    }
}

