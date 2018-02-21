/*
** my_strlen.c for minishell2 in /home/Rubiks/PSU/PSU_2016_minishell2/lib
** 
** Made by Maxime BLANCHARD
** Login   <Rubiks@epitech.net>
** 
** Started on  Mon Mar 27 17:00:13 2017 Maxime BLANCHARD
** Last update Mon Mar 27 17:00:24 2017 Maxime BLANCHARD
*/

int     my_strlen(char *str)
{
  int   i;

  i = 0;
  while (str[i] != '\0')
    i = i + 1;
  return (i);
}
