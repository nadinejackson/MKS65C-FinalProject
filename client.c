#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  char * junk = malloc(sizeof(char));
  char * line = malloc(1024 * sizeof(char));
  from_server = client_handshake( &to_server );
  write(to_server, "h", 1024 * sizeof(char));
  while(1)
    {
      //perror("error");
      if (read(from_server, line, 1024 * sizeof(char)))
	{
	  printf("\033[2J\033[;H");
	  printf("%s\n", line);
	}
      else
	{
	  perror("error reading");
	  exit(0);
	}
      if (strcmp(line, "Game Over!"))
	{
	  printf("Please type the letters corresponding to a set and press enter.\nEnter r to refresh.\nEnter h for help.\nEnter 3 to add cards.\n");
	  fscanf(stdin, "%[^\n]s", line);
	  fscanf(stdin, "%c", junk);
	  write(to_server, line, 1024 * sizeof(char));
	}
      else
	break;
    }
  return 0;
}
