/*
** main.c for N4S in /home/Rubiks/CPE/CPE_2016_n4s/CPE_2016_n4s/srcs
** 
** Made by Maxime BLANCHARD
** Login   <Rubiks@epitech.net>
** 
** Started on  Sun May  7 19:12:44 2017 Maxime BLANCHARD
** Last update Sat Jun  3 13:12:17 2017 Maxime BLANCHARD
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include "my.h"

double g_speed = 0.2;
double g_wheels = 0;

int                     new_direction(t_info_lidar *lidar, int direction)
{
  g_wheels = calc_wheels(lidar);
  brakes(g_wheels);
  if (g_wheels > 0.08)
    return (stabilizator(direction));
  else
    return (0);
}

void            set_speed(double speed)
{
  g_speed = speed;
  if (g_speed > 1)
    g_speed = 1;
  else if (g_speed < 0)
    g_speed = 0;
  fprintf(stderr, "Speed : %.2f\n", g_speed);
  exec_instruction(CAR_FORWARD, g_speed);
}

int		emergency_case()
{
  static int    count = 0;

  fprintf(stderr, "\x1B[31mIA must go backward...\n\x1B[0m");
  exec_instruction(WHEELS_DIR, (g_wheels = 0));
  exec_instruction(CAR_BACKWARDS, 0.2);
  exec_instruction(CYCLE_WAIT, 30);
  set_speed(0.15);
  if (count > 4)
    {
      fprintf(stderr, "\x1B[31mIA must stop...\n\x1B[0m");
      return (1);
    }
  count = count + 1;
  return (0);
}

int             get_info_lidar(t_info_lidar **infos)
{
  t_answer      *ans;

  if ((*infos = malloc(sizeof(t_info_lidar))) == NULL)
    return (1);
  ans = exec_instruction(GET_INFO_LIDAR);
  (*infos)->left = do_average(ans->ans2->infos, 0, 3);
  (*infos)->m_left = do_average(ans->ans2->infos, 3, 8);
  (*infos)->middle = do_average(ans->ans2->infos, 11, 10);
  (*infos)->m_right = do_average(ans->ans2->infos, 21, 8);
  (*infos)->right = do_average(ans->ans2->infos, 29, 3);
  if (detect_col(ans->ans2->infos) > 4)
    return (emergency_case());
  return (0);
}

int		main()
{
  t_info_lidar	*lidar;
  t_info_sim	*info_sim;
  int	i;
  int	fifo;

  if ((info_sim = malloc(sizeof(t_info_sim))) == NULL)
    return (0);
  fifo = open("n4s_siminfo.fifo", O_WRONLY | O_NONBLOCK);
  g_memory = load_memory("MEMORY");
  exec_instruction(START_SIMULATION);
  set_speed(g_speed);
  i = get_info_lidar(&lidar);
  while (i != 1)
    {
      info_sim->speed = g_speed;
      info_sim->wheels = g_wheels;
      if (fifo != -1)
	write(fifo, info_sim, sizeof(t_info_sim));
      i = get_info_lidar(&lidar);
      set_direction(lidar);
      free(lidar);
    }
  set_speed(0);
  exec_instruction(STOP_SIMULATION);
  return (0);
}
