/*
** my_strcmp.c for minishell2 in /home/Rubiks/PSU/PSU_2016_minishell2
** 
** Made by Maxime BLANCHARD
** Login   <Rubiks@epitech.net>
** 
** Started on  Sat Mar 25 19:05:12 2017 Maxime BLANCHARD
** Last update Mon Mar 27 16:44:22 2017 Maxime BLANCHARD
*/

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  while (s1[i] == s2[i] && s1[i] != '\0')
    i = i + 1;
  return (s1[i] - s2[i]);
}
