#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char * buf = malloc(1024 * sizeof(char));
  char message[1024] = "received";
  
  //create wkp and wait for connection
  mkfifo("waluigi", 0644);
  perror("pls tell me everything's okay");
  printf("pipe created\n");
  
  //client creates "private" fifo

  //client sends message to server, waits for response
  
  //server recieves client's message and removes the wkp
  int from_client = open("waluigi", O_RDONLY, 0644);
  printf("pipe opened: %d\n", from_client);
  read(from_client, buf, 1024 * sizeof(char));
  printf("path name: %s\n", buf);  
  remove("./waluigi");
  

  int f = fork();
  if (f) //parent
    return from_client;
  else
    {
      //server connects to client and sends acknowledgement
      int tc = open(buf, O_WRONLY, 0644);
      *to_client = tc;
      printf("acknowledgement to write: %s\n", message);
      write(tc, message, 1024 * sizeof(char));

      //client recieves server's message, removes private fifo

      //client sends response to server
      read(from_client, buf, 1024 * sizeof(char));
      printf("second message recieved: %s\n", buf);  

      free(buf);
      return from_client;
    }
}

int client_handshake(int *to_server) {
  char * buf = malloc(1024 * sizeof(char));
  char path[1024] = "./waaah";
  
  //server create wkp and wait for connection
  
  //client creates "private" fifo
  mkfifo(path, 0644);
  printf("response pipe created\n");

  
  //client sends message to server
  int ts = open("./waluigi", O_WRONLY, 0644);
  *to_server = ts;
  write(ts, path, 1024 * sizeof(char));
  printf("path name written: %s\n", path);  
  int from_server = open(path, O_RDONLY);
  //server recieves client's message and removes the wkp
  
  //server connects to client and sends acknowledgement

  //client recieves server's message, removes its private fifo
  read(from_server, buf, 1024 * sizeof(char));
  perror("error reading");
  printf("got a message from the server and it was this: %s\n", buf);
  remove("waaah");

  //client sends a response to the server
  write(ts, "check", 1024 * sizeof(char));

  free(buf);
  return from_server;
}
