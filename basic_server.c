#include "pipe_networking.h"


int main() {
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
	      strcat(buf, ", but death is inevitable.");
	      write(to_client, buf, 1024 * sizeof(char));
	    }
	  else
	    exit(0);
	}
      else
	from_client = server_handshake( &to_client );
    }
}
