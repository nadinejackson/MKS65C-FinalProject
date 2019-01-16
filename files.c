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
  int locations[30] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  write(fd, locations, 30 * sizeof(int));
  close(fd);
}

int check(int locations[], int * place, int playerno)
{
  int data[30];
  int fd = open("./.setgame", O_RDONLY, 0666);
  read(fd, data, 30 * sizeof(int));
  int retval = *place - data[15];
  close(fd);
  return retval;
}

int update(int locations[], int * place, int playerno)
{
  int data[30];
  int points;

  int fd = open("./.setgame", O_RDONLY, 0666);
  read(fd, data, 30 * sizeof(int));
  points = data[16 + playerno];
  points += 1;
  *place = data[15];
  close(fd);
  
  int i;
  for(i = 0; i < 15; i++)
    data[i] = locations[i];
  data[15] = *place;

  fd = open("./.setgame", O_WRONLY, 0666);
  write(fd, data, 30 * sizeof(int));
  close(fd);
  return points;
  }
int update_loss(int locations[], int * place, int playerno)
{
  int data[30];
  int fd = open("./.setgame", O_RDONLY, 0666);
  read(fd, data, 30 * sizeof(int));
  int i;
  for(i = 0; i < 15; i++)
    locations[i] = data[i];
  *place = data[15];
  close(fd);
  return data[16 + playerno];
}
