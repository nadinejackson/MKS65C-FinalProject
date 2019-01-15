#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>


void create()
{
  int fd = open("./.setgame", O_CREAT | O_WRONLY, 0666);
  int locations[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 12, 0, 0};
  write(fd, locations, 18 * sizeof(int));
  close(fd);
}

int check(int locations[], int * place, int playerno)
{
  int data[18];
  int fd = open("./.setgame", O_RDONLY, 0666);
  read(fd, data, 18 * sizeof(int));
  int retval = *place - data[15];
  close(fd);
  return retval;
}

void update(int locations[], int * place, int playerno, int points)
{
  int data[18];
  int i;
  for(i = 0; i < 15; i++)
    data[i] = locations[i];
  data[15] = *place;
  data[16] = points;
  int fd = open("./.setgame", O_WRONLY, 0666);
  write(fd, data, 18 * sizeof(int));
  close(fd);
}
void update_loss(int locations[], int * place, int * playerno)
{
  int data[18];
  int fd = open("./.setgame", O_RDONLY, 0666);
  read(fd, data, 18 * sizeof(int));
  int i;
  for(i = 0; i < 15; i++)
    locations[i] = data[i];
  *place = data[15];
  close(fd);
}
