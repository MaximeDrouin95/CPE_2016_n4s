/*
** get_next_line.c for get_next_line in /home/alkoleek
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Thu Jan  5 15:04:24 2017 Maxime DROUIN
** Last update Mon Feb 13 21:08:32 2017 Maxime DROUIN
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

t_llist		gnl_add_last(t_llist list, char val)
{
  t_llist	new_list;
  t_llist	temp;

  temp = list;
  if ((new_list = malloc(sizeof(t_element))) == NULL)
    return (NULL);
  new_list->val = val;
  new_list->nxt = NULL;
  if (list == NULL)
    return (new_list);
  else
    while (temp->nxt != NULL)
      temp = temp->nxt;
  temp->nxt = new_list;
  return (list);
}

t_llist		gnl_del_first(t_llist list)
{
  t_llist	new_list;

  new_list = list->nxt;
  if (list != NULL)
    {
      free(list);
      return (new_list);
    }
  else
    return (NULL);
}

char		*gnl_conv_llist(t_llist list, t_llist temp)
{
  int		count;
  char		*array;
  int		i;

  i = 0;
  count = 0;
  while (temp->val != '\n')
    {
      temp = temp->nxt;
      count = count + 1;
    }
  if ((array = malloc(sizeof(char) * count + 1)) == NULL)
    return (NULL);
  while (list->val != '\n')
    {
      array[i] = list->val;
      list = list->nxt;
      i = i + 1;
    }
  array[i] = '\0';
  return (array);
}

char			*gnl_llist_to_array(t_llist list)
{
  char			*array;
  static t_llist	list_static = NULL;
  t_llist		temp;

  while (list != NULL)
    {
      list_static = gnl_add_last(list_static, list->val);
      list = gnl_del_first(list);
    }
  if (list_static == NULL)
    return (NULL);
  temp = list_static;
  array = gnl_conv_llist(list_static, temp);
  while (list_static->val != '\n')
    list_static = gnl_del_first(list_static);
  if (list_static->val == '\n')
    list_static = gnl_del_first(list_static);
  return (array);
}

char		*get_next_line(const int fd)
{
  char		*buffer;
  t_llist	line;
  int		count;
  int		i;
  int		end;

  buffer = gnl_init(&i, &end, &line);
  while (end != -1 && (i = read(fd, buffer, READ_SIZE)) > 0)
    {
      count = 0;
      buffer[i]  = '\0';
      while (buffer[count] != '\0')
	{
	  if (buffer[count] == '\n')
	    end = -1;
	  line = gnl_add_last(line, buffer[count]);
	  count = count + 1;
	}
      if (i < READ_SIZE && buffer[count - 1] != '\n')
	line = gnl_add_last(line, '\n');
      if (i < READ_SIZE && end == 0 && fd == 0 && i > 0)
	break;
    }
  free(buffer);
  return (gnl_llist_to_array(line));
}
