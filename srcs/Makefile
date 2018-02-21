##
## Makefile for minishell2 in /home/Rubiks/PSU/PSU_2016_minishell2/lib
## 
## Made by Maxime BLANCHARD
## Login   <Rubiks@epitech.net>
## 
## Started on  Mon Mar 27 17:04:48 2017 Maxime BLANCHARD
## Last update Sun May  7 19:52:52 2017 Maxime BLANCHARD
##

RM      =       rm -f

NAME    =       ../libgnl.a

SRCS    =       get_next_line.c         	\
		get_next_line_init.c		\

OBJS    =       $(SRCS:.c=.o)

all:    $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
