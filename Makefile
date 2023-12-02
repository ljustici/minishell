# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/02 14:51:07 by ljustici          #+#    #+#              #
#    Updated: 2023/11/22 16:23:40 by ljustici         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

LIBFT := libft/libft.a

SRC_DIR		:= src/
_SRCS       := lexer.c lexer_split.c lexer_utils.c lexer_split_qt.c \
				lexer_count_utils.c parser.c parser_errors.c parser_naming.c \
				parser_utils.c parser_list.c parser_syntax.c

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