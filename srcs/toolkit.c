/*
** toolkit.c for n4s in /home/alkoleek/CPE_2016_n4s
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sat Jun  3 14:28:23 2017 Maxime DROUIN
** Last update Sat Jun  3 14:28:23 2017 Maxime DROUIN
*/

#include <math.h>
#include <stdlib.h>
#include "my.h"

t_info_lidar    *dup_lidar(t_info_lidar *lidar)
{
  t_info_lidar  *cpy;

  if ((cpy = malloc(sizeof(t_info_lidar))) == NULL)
    return (NULL);
  cpy->left = lidar->left;
  cpy->m_left = lidar->m_left;
  cpy->middle = lidar->middle;
  cpy->m_right = lidar->m_right;
  cpy->right = lidar->right;
  return (cpy);
}

int             check_memory_dup(t_memory *memory, t_info_lidar *lidar,
				 double offset)
{
  if (fabs(lidar->left - memory->lidar->left) <= offset
      && fabs(lidar->m_left - memory->lidar->m_left) <= offset
      && fabs(lidar->middle - memory->lidar->middle) <= offset
      && fabs(lidar->m_right - memory->lidar->m_right) <= offset
      && fabs(lidar->right - memory->lidar->right) <= offset
      && fabs(g_speed - memory->speed) <= 0.1)
    return (1);
  return (0);
}

int     detect_col(double *infos)
{
  int   i;
  int   count;

  i = 0;
  count = 0;
  while (i < 32)
    {
      if (infos[i] < 100 * g_speed)
	count = count + 1;
      i = i + 1;
    }
  return (count);
}

int             do_average(double *tab, int zone, int offset)
{
  int           average;
  int           i;

  average = 0;
  i = zone;
  while (i < zone + offset)
    {
      average = average + (int)tab[i];
      i = i + 1;
    }
  average = average / offset;
  return (average);
}
