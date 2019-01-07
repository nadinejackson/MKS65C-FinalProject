#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  char * junk = malloc(sizeof(char));
  char * line = malloc(1024 * sizeof(char));
  from_server = client_handshake( &to_server );
  while(1)
    {
      printf("hello. please type something and press enter.\n");
      fscanf(stdin, "%[^\n]s", line);
      fscanf(stdin, "%c", junk);
      write(to_server, line, 1024 * sizeof(char));
      if (read(from_server, line, 1024 * sizeof(char)))
	printf("%s\n", line);
      else
	exit(0);
    }
  return 0;
}
