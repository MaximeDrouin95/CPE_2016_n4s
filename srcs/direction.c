/*
** direction.c for n4s in /home/alkoleek/CPE_2016_n4s
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sat Jun  3 14:27:13 2017 Maxime DROUIN
** Last update Sat Jun  3 14:27:13 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

double          calc_wheels(t_info_lidar *lidar)
{
  double        x;
  double        step;
  double        angle;
  double        result;

  result = 0;
  angle = ANGLE_SIZE;
  step = STEP_SIZE;
  x = MAX_DETECT;
  fprintf(stderr, "Distance from the turn : ");
  while (x > step && (x > lidar->middle ||
		   x + 100 > lidar->m_left || x + 100 > lidar->m_right))
    {
      result = result + angle;
      if (x == 570 || x == 270)
	{
	  step = step / 2;
	  angle = angle + 0.009;
	}
      x = x - step;
    }
  fprintf(stderr, "%.2f\n", x);
  return (result);
}

void		set_direction(t_info_lidar *lidar)
{
  static int	old_dir = 0;

  if (lidar->middle <= 1000 || lidar->left < 470
      || lidar->right < 470 || lidar->m_right < 575 || lidar->m_left < 575)
    {
      if ((lidar->left < lidar->right && lidar->right > 250)
	  || (lidar->m_right > 575 && lidar->m_right > lidar->m_left
	      && lidar->right > lidar->m_left))
	old_dir = direction(lidar, DIR_R);
      else if ((lidar->right < lidar->left && lidar->left > 250)
	       || (lidar->m_left > 575 && lidar->m_left > lidar->m_right
		   && lidar->left > lidar->m_right))
	old_dir = direction(lidar, DIR_L);
      else
	direction(lidar, old_dir);
      if (g_speed < 0.2)
	set_speed(g_speed + 0.01);
    }
  else
    {
      exec_instruction(WHEELS_DIR, (g_wheels = 0));
      if (g_speed < 0.75 && lidar->middle > 1200)
	set_speed(g_speed + 0.05);
    }
}

void			brakes(double k)
{
  if (k > 0.02)
    {
      if (g_speed >= 0.39)
	set_speed(g_speed - 0.3);
      else if (g_speed <= 0.19 && g_speed > 0.1)
	set_speed(g_speed - 0.02);
    }
}

int                     direction(t_info_lidar *lidar, int direction)
{
  int                   i;
  static t_info_lidar   *save = NULL;

  i = 0;
  if (save != NULL)
    correct_memory(lidar, &save, direction);
  if ((g_wheels = get_memory_dir(g_memory, lidar, &g_speed)) == 84)
    i = new_direction(lidar, direction);
  else
    save = dup_lidar(lidar);
  if (i != 0)
    return (direction);
  g_memory = add_memory(g_memory, lidar, g_wheels, g_speed);
  if (direction == DIR_L)
    fprintf(stderr, "Going \x1B[33mLEFT\x1B[0m with ");
  else
    fprintf(stderr, "Going \x1B[34mRIGHT\x1B[0m with ");
  fprintf(stderr, "angle : %.2f\n", g_wheels);
    exec_instruction(WHEELS_DIR, (g_wheels = g_wheels * direction));
  i = 3 - (int)(g_speed * 10);
  if (i > 0)
    exec_instruction(CYCLE_WAIT, i);
  return (direction);
}

int             stabilizator(int direction)
{
  static int    old_d = 0;

  if (old_d != direction)
    {
      fprintf(stderr, "\t\t\x1B[35mIA : stabilizating\x1B[0m to ");
      if (direction == DIR_L)
	fprintf(stderr, "\x1B[33mLEFT\n\x1B[0m");
      else
	fprintf(stderr, "\x1B[34mRIGHT\n\x1B[0m");
      exec_instruction(WHEELS_DIR, (g_wheels = 0.02 * (double)direction));
      old_d = direction;
      return (1);
    }
  old_d = direction;
  return (0);
}
