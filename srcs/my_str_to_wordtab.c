/*
** str_to_wordtab.c for LIBRARY in /home/Rubiks/TEST_AREA/misc/str_to_wortab
** 
** Made by Maxime BLANCHARD
** Login   <Rubiks@epitech.net>
** 
** Started on  Tue May  2 10:34:18 2017 Maxime BLANCHARD
** Last update Sun May  7 19:45:28 2017 Maxime BLANCHARD
*/

#include <stdlib.h>
#include <stdio.h>

void	stw_free(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    {
      free(tab[i]);
      i = i + 1;
    }
  free(tab);
}

int	stw_size(char *str, char *sep)
{
  int	i;
  int	j;
  int	count;

  i = 0;
  j = 0;
  count = 0;
  while (str[i] && str[i] != sep[j])
    {
      j = j + 1;
      if (!sep[j])
	{
	  count = count + 1;
	  i = i + 1;
	  j = 0;
	}
    }
  return (count);
}

int	stw_words(char *str, char *sep)
{
  int	i;
  int	j;
  int	count;
  int	is_word;

  i = 0;
  count = 0;
  while (str != NULL && str[i])
    {
      j = 0;
      is_word = 0;
      while (str[i] && str[i] != sep[j])
	{
	  j = j + 1;
	  if (!sep[j])
	    {
	      is_word = 1;
	      i = i + 1;
	      j = 0;
	    }
	}
      count = count + is_word;
      i = i + 1;
    }
  return (count);
}

char	*stw_split(char *str, char *sep, int *i)
{
  char	*line;
  int	k;
  int	l;

  k = 0;
  l = 0;
  if (stw_size(&str[*i], sep) == 0)
    return (NULL);
  if ((line = malloc(sizeof(char) * (stw_size(&str[*i], sep) + 1))) == NULL)
    return (NULL);
  while (str[*i] && str[*i] != sep[l])
    {
      l = l + 1;
      if (!sep[l])
	{
	  line[k] = str[*i];
	  *i = *i + 1;
	  k = k + 1;
	  l = 0;
	}
    }
  line[k] = 0;
  if (str[*i])
    *i = *i + 1;
  return (line);
}

char	**str_to_wordtab(char *str, char *sep)
{
  char	**wordtab;
  int	i;
  int	j;
  int	k;

  i = 0;
  j = 0;
  if ((k = stw_words(str, sep)) == 0)
    return (NULL);
  if (str == NULL)
    return (NULL);
  if ((wordtab = malloc(sizeof(char *) * (stw_words(str, sep) + 1))) == NULL)
    return (NULL);
  while (str[i] != 0)
    {
      if ((wordtab[j] = stw_split(str, sep, &i)) != NULL)
	j = j + 1;
      else
	i = i + 1;
    }
  wordtab[j] = NULL;
  return (wordtab);
}
