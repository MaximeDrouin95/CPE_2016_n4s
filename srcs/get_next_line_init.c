/*
** get_next_line_init.c for get_next_line in /home/alkoleek/SEMESTER_1/CPE_SEMESTER_1/CPE_2016_getnextline
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Thu May 11 11:09:08 2017 Maxime DROUIN
** Last update Thu May 11 11:09:08 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "get_next_line.h"

char	*gnl_init(int *i, int *end, t_llist *list)
{
  char	*buffer;

  (*list) = NULL;
  (*i) = 0;
  (*end) = 0;
  buffer = malloc(sizeof(char) * (READ_SIZE + 1));
  return (buffer);
}
