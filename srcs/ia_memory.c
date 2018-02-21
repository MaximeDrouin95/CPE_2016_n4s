/*
** ia_memory.c for n4s in /home/alkoleek/CPE_2016_n4s
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sat Jun  3 14:29:35 2017 Maxime DROUIN
** Last update Sat Jun  3 14:29:35 2017 Maxime DROUIN
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

t_memory        *g_memory = NULL;

double          check_angle(t_info_lidar *lidar, t_info_lidar *previous,
			    double angle, int direction)
{
  double        save_angle = fabs(angle);
  double        offset = 60;
  double        i;

  if (lidar->left < previous->left &&
      (i = fabs(lidar->left - previous->left)) > offset)
    {
      if (direction == DIR_L && angle > 0.01)
	angle = angle - 0.01;
      else if (direction == DIR_R && angle < 0.99)
	angle = angle + 0.01;
    }
  else if (lidar->right < previous->right &&
	   (i = fabs(lidar->right - previous->right)) > offset)
    {
      if (direction == DIR_L && angle < 0.99)
	angle = angle + 0.01;
      else if (direction == DIR_R && angle > 0.01)
	angle = angle - 0.01;
    }
  if (save_angle != fabs(angle))
    fprintf(stderr, "\t\t\x1B[35mIA : Updated angle %.2f to %.2f\n\x1B[0m",
	    save_angle, fabs(angle));
  return (fabs(angle));
}

t_memory        *add_memory(t_memory *memory, t_info_lidar *lidar,
			    double angle, double speed)
{
  t_memory      *new;
  t_memory      *temp;

  if ((new = malloc(sizeof(t_memory))) == NULL)
    return (NULL);
  temp = memory;
  while (temp != NULL)
    {
      if (check_memory_dup(memory, lidar, 10) != 0)
	{
	  fprintf(stderr, "\t\t\x1B[31mIA : Dup information\n\x1B[0m");
	  return (memory);
	}
      temp = temp->next;
    }
  new->angle = angle;
  new->speed = speed;
  if ((new->lidar = dup_lidar(lidar)) == NULL)
    return (NULL);
  new->next = memory;
  return (new);
}

double          get_memory_dir(t_memory *memory, t_info_lidar *lidar,
			       double *speed)
{
  t_memory      *temp;
  double        i;
  double        result;
  double	t_speed;

  temp = i_gmemdir(memory, &i, &result, &t_speed);
  while (temp != NULL)
    {
      if (check_memory_dup(temp, lidar, 20))
	{
	  result = result + temp->angle;
	  t_speed = t_speed + temp->speed;
	  i = i + 1;
	}
      temp = temp->next;
    }
  if (i != 0)
    {
      fprintf(stderr, "\t\t\x1B[36mIA : Speed=%.2f Wheels=%.2f\n\x1B[0m",
	      ((*speed) = t_speed / i), result / i);
      set_speed((*speed));
      return (result / i);
    }
  return (84);
}

void            correct_memory(t_info_lidar *lidar, t_info_lidar **save,
			       int direction)
{
  t_memory      *temp;
  double	x;

  temp = g_memory;
  while (temp != NULL)
    {
      x = temp->angle;
      if (check_memory_dup(temp, (*save), 10))
	{
	  temp->angle = check_angle(lidar, (*save), temp->angle, direction);
	  if (x != temp->angle && temp->speed > 0.15)
	    temp->speed = temp->speed - 0.01;
	}
      temp = temp->next;
    }
  (*save) = NULL;
}

void            show_memory(t_memory *memory)
{
  t_memory      *temp;

  temp = memory;
  while (temp != NULL)
    {
      fprintf(stderr, "Lidar : %.2f %.2f %.2f %.2f %.2f\n",
	      temp->lidar->left, temp->lidar->m_left, temp->lidar->middle,
	      temp->lidar->m_right, temp->lidar->right);
      fprintf(stderr, "Angle : %.2f\nSpeed : %.2f\n",
	      temp->angle, temp->speed);
      temp = temp->next;
    }
}
