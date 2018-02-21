/*
** get_answer_tools.c for ai in /home/alkoleek/CPE_2016_n4s
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Thu May  4 14:30:56 2017 Maxime DROUIN
** Last update Thu May  4 14:30:56 2017 Maxime DROUIN
*/

#include "my.h"

bool    get_status(char *str)
{
  if (my_strcmp(str, "OK") == 0)
    return (TRUE);
  else
    return (FALSE);
}
