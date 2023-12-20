# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 12:22:05 by ljustici          #+#    #+#              #
#    Updated: 2023/08/15 18:21:22 by ljustici         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_split.c \
			ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
			ft_substr.c ft_tolower.c ft_toupper.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_printf.c ft_print_flag_content.c ft_latoi.c ft_strcmp.c \

OBJS	=	$(SRCS:.c=.o)

BONUS	=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \

BOBJS	=	$(BONUS:.c=.o)

CC		=	gcc

CFLAGS	=	-Werror -Wextra -Wall

RM		=	rm -f

all:	$(NAME)

$(NAME):
	$(CC) -c $(CFLAGS) $(SRCS)
	ar rcs $(NAME) $(OBJS)

bonus:
	$(CC) -c $(CFLAGS) $(SRCS) $(BONUS)
	ar rcs $(NAME) $(OBJS) $(BOBJS)

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all

.PHONY: all, clean, fclean, re, bonus