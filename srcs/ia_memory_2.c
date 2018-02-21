/*
** ia_memory_2.c for n4s in /home/alkoleek/CPE_2016_n4s
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sat Jun  3 14:37:16 2017 Maxime DROUIN
** Last update Sat Jun  3 14:37:16 2017 Maxime DROUIN
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"

t_memory        *load_element(t_info_lidar *lidar, int fd, t_memory *memory)
{
  double        angle;
  double        speed;

  read(fd, &angle, sizeof(double));
  read(fd, &speed, sizeof(double));
  memory = add_memory(memory, lidar, angle, speed);
  return (memory);
}

t_memory        *load_memory(char *filename)
{
  int           fd;
  t_info_lidar  *lidar;
  t_memory      *memory;
  int           i;

  memory = NULL;
  if ((lidar = malloc(sizeof(t_info_lidar))) == NULL)
    return (NULL);
  fd = open(filename, O_RDONLY);
  while (read(fd, lidar, sizeof(t_info_lidar)) > 0)
    {
      memory = load_element(lidar, fd, memory);
      i = i + 1;
    }
  fprintf(stderr, "\t\t\x1B[32mIA : %d elements loaded\n\x1B[0m", i);
  close(fd);
  return (memory);
}

t_memory            *i_gmemdir(t_memory *memory, double *i, double *result,
			      double *t_speed)
{
  (*i) = 0;
  (*t_speed) = 0;
  (*result) = 0;
  return (memory);
}
