/*
** action_exec.c for ai in /home/alkoleek/CPE_2016_n4s
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Thu May  4 14:33:46 2017 Maxime DROUIN
** Last update Sun May  7 19:49:34 2017 Maxime BLANCHARD
*/

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my.h"

t_command       g_commands[13] = {{"START_SIMULATION", NONE_VAR, 1},
				  {"STOP_SIMULATION", NONE_VAR, 1},
				  {"CAR_FORWARD", F_VAR, 1},
				  {"CAR_BACKWARDS", F_VAR, 1},
				  {"WHEELS_DIR", F_VAR, 1},
				  {"GET_INFO_LIDAR", NONE_VAR, 2},
				  {"GET_CURRENT_SPEED", NONE_VAR, 3},
				  {"GET_CURRENT_WHEELS", NONE_VAR, 3},
				  {"CYCLE_WAIT", I_VAR, 1},
				  {"GET_CAR_SPEED_MAX", NONE_VAR, 3},
				  {"GET_CAR_SPEED_MIN", NONE_VAR, 3},
				  {"GET_INFO_SIMTIME", NONE_VAR, 4},
				  {0, 0, 0}};

int		check_answer(t_answer **ans)
{
  if ((*ans)->status == FALSE)
    {
      fprintf(stderr, "\x1B[31mError : %s\n\x1B[0m", (*ans)->code_str);
      free((*ans));
      return (1);
    }
  return (0);
}

void		save_memory()
{
  int		save;
  t_memory	*temp;

  temp = g_memory;
  if ((save = open("MEMORY", O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
    return ;
  while (temp != NULL)
    {
      write(save, temp->lidar, sizeof(t_info_lidar));
      write(save, &temp->angle, sizeof(double));
      write(save, &temp->speed, sizeof(double));
      temp = temp->next;
    }
  close(save);
}

void		free_memory(t_memory *memory)
{
  t_memory	*temp;
  t_memory	*temp2;

  temp = memory;
  while (temp != NULL)
    {
      free(temp->lidar);
      temp2 = temp->next;
      free(temp);
      temp = temp2;
    }
}

int	check_additional(t_answer *ans)
{
  if (my_strcmp(ans->additionnal_info, "Track Cleared") == 0)
    {
      exec_instruction(WHEELS_DIR, (g_wheels = 0));
      while (g_speed > 0)
	set_speed(g_speed - 0.3);
      save_memory();
      fprintf(stderr, "\x1B[32mTrack Cleared\n\x1B[0m");
      ans = exec_instruction(GET_INFO_SIMTIME);
      fprintf(stderr, "Time spent on the track : \x1B[32m[%lld secs]\n\x1B[0m",
	      ans->ans4->time_sec);
      exec_instruction(STOP_SIMULATION);
      free_memory(g_memory);
      exit(256);
    }
  else if (my_strcmp(ans->additionnal_info, "No further info") != 0)
    fprintf(stderr, "\x1B[33m%s\n\x1B[0m", ans->additionnal_info);
  return (0);
}

t_answer        *exec_instruction(int code, ...)
{
  va_list       ap;
  t_answer	*ans;

  setbuf(stdout, NULL);

  printf("%s", g_commands[code].cmd);
  if (g_commands[code].var_type != NONE_VAR)
    {
      va_start(ap, code);
      printf(":");
      if (g_commands[code].var_type == F_VAR)
	printf("%.2f", va_arg(ap, double));
      else if (g_commands[code].var_type == I_VAR)
	printf("%d", va_arg(ap, int));
      va_end(ap);
    }
  printf("\n");
  if ((ans = get_answer(get_next_line(0),
			g_commands[code].answer_type)) == NULL
      || check_answer(&ans) != 0)
    {
      free_memory(g_memory);
      exit(84);
    }
  check_additional(ans);
  return (ans);
}
