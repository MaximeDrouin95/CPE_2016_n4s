/*
** get_next_line.h for get_next_line in /home/alkoleek/CPE_2016_getnextline
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Fri Jan  6 13:54:24 2017 Maxime DROUIN
** Last update Mon Feb 13 21:09:33 2017 Maxime DROUIN
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_
#define READ_SIZE (65536)
typedef struct s_element t_element;
struct s_element
{
  char           val;
  struct s_element *nxt;
};
typedef t_element* t_llist;
char	*gnl_init(int *, int *, t_llist *);
t_llist	gnl_add_last(t_llist, char);
t_llist	gnl_del_first(t_llist);
char	*gnl_conv_llist(t_llist, t_llist);
char	*gnl_llist_to_array(t_llist);
char	*get_next_line(const int);
#endif
