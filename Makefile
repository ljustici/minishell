# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 14:51:07 by ljustici          #+#    #+#              #
#    Updated: 2023/10/03 19:22:41 by ljustici         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

LIBFT := libft/libft.a

SRC_DIR		:= src/
_SRCS       := pipex.c parse_pipex.c

SRCS		:= ${addprefix ${SRC_DIR}, ${_SRCS}}
OBJS		:= $(SRCS:.c=.o)

CC          := @gcc
CFLAGS      := -Wall -Wextra -Werror

RM          := @rm -rf
MAKE        := @$(MAKE) --silent --no-print-directory

all:  ${LIBFT} $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) ${LIBFT} $(OBJS) -o $(NAME)
	$(info created $(NAME))

clean:
	$(RM) $(OBJS)
	$(info cleaned object files)

fclean: clean
	$(RM) $(NAME) checker
	$(MAKE) -C ./libft fclean
	$(info cleaned minishell)

re: fclean all

.PHONY: all bonus clean fclean re