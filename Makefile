##
## Makefile for N4S in /home/Rubiks/CPE/CPE_2016_n4s/CPE_2016_n4s
## 
## Made by Maxime BLANCHARD
## Login   <Rubiks@epitech.net>
## 
## Started on  Sun May  7 19:53:11 2017 Maxime BLANCHARD
## Last update Wed May 10 13:15:05 2017 Maxime BLANCHARD
##

CC      =       gcc -I ./lib/ -I include/

LDFLAGS	=	 -lm

CFLAGS +=	-Wall -Wextra -Werror -W

RM      =       rm -f

NAME    =       ai

SRCS    =	srcs/get_next_line.c		\
		srcs/get_next_line_init.c	\
		srcs/main.c			\
		srcs/action_exec.c		\
		srcs/get_answer.c		\
		srcs/get_answer_tools.c		\
		srcs/direction.c		\
		srcs/toolkit.c			\
		srcs/ia_memory.c		\
		srcs/ia_memory_2.c		\
		srcs/my_strcmp.c                \
		srcs/my_str_to_wordtab.c	\
		srcs/my_strlen.c                

OBJS    =       $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
