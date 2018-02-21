/*
** get_answer.c for ai in /home/alkoleek/CPE_2016_n4s
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Thu May  4 14:24:51 2017 Maxime DROUIN
** Last update Tue May  9 14:59:17 2017 Maxime BLANCHARD
*/

#include <string.h>
#include <stdlib.h>
#include "my.h"

t_answer	*g_answer_1(t_answer *out, char **parse)
{
  out->additionnal_info = strdup(parse[3]);
  out->ans2 = NULL;
  out->ans3 = NULL;
  out->ans4 = NULL;
  return (out);
}

t_answer	*g_answer_2(t_answer *out, char **parse)
{
  int		i;
  int		j;

  i = 3;
  j = 0;
  if ((out->ans2 = malloc(sizeof(t_ans2))) == NULL)
    return (NULL);
  while (j < 32)
    {
      out->ans2->infos[j] = atof(parse[i]);
      j = j + 1;
      i = i + 1;
    }
  out->additionnal_info = strdup(parse[i]);
  out->ans3 = NULL;
  out->ans4 = NULL;
  return (out);
}

t_answer     *g_answer_3(t_answer *out, char **parse)
{
  if ((out->ans3 = malloc(sizeof(t_ans3))) == NULL)
    return (NULL);
  out->ans3->speed = atof(parse[3]);
  out->additionnal_info = strdup(parse[4]);
  out->ans2 = NULL;
  out->ans4 = NULL;
  return (out);
}

t_answer	*g_answer_4(t_answer *out, char **parse)
{
  char		**pars_nb;

  if ((out->ans4 = malloc(sizeof(t_ans4))) == NULL)
    return (NULL);
  parse[3][my_strlen(parse[3]) - 1] = 0;
  parse[3] = parse[3] + 1;
  if ((pars_nb = str_to_wordtab(parse[3], ",")) == NULL)
    return (NULL);
  out->ans4->time_sec = atoll(pars_nb[0]);
  out->ans4->time_ns = atoll(pars_nb[1]);
  out->additionnal_info = strdup(parse[4]);
  out->ans2 = NULL;
  out->ans3 = NULL;
  return (out);
}

static t_answer *(*g_fill_answer[5])(t_answer *, char **) = {g_answer_1,
							     g_answer_2,
							     g_answer_3,
							     g_answer_4,
							     0};

t_answer        *get_answer(char *str, int answer_type)
{
  t_answer      *out;
  char          **parse;

  if ((out = malloc(sizeof(t_answer))) == NULL)
    return (NULL);
  if ((parse = str_to_wordtab(str, ":")) == NULL)
    return (NULL);
  out->type = answer_type;
  if (parse[0] != NULL)
    out->value_id = atoi(parse[0]);
  if (parse[1] != NULL)
    out->status = get_status(parse[1]);
  if (parse[2] != NULL)
    out->code_str = strdup(parse[2]);
  if ((out = g_fill_answer[answer_type - 1](out, parse)) == NULL)
    return (NULL);
  return (out);
}
