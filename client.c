#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  char * junk = malloc(sizeof(char));
  char * line = malloc(1024 * sizeof(char));
  from_server = client_handshake( &to_server );
  write(to_server, "let's start", 1024 * sizeof(char));
  while(1)
    {
      //perror("error");
      if (read(from_server, line, 1024 * sizeof(char)))
	printf("%s\n", line);
      else
	{
	  perror("error reading");
	  exit(0);
	}
      printf("hello. please type the letters in a set and press enter.\n");
      fscanf(stdin, "%[^\n]s", line);
      fscanf(stdin, "%c", junk);
      write(to_server, line, 1024 * sizeof(char));
      
    }
  return 0;
}
