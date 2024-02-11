# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 13:12:22 by roruiz-v          #+#    #+#              #
#    Updated: 2024/02/11 12:51:07 by ljustici         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIB = -L $(HOME)/.brew/opt/readline/lib -lreadline

# LIB para casa_rosana:
#LIB = -L/usr/local/opt/readline/lib -lreadline

INCLUDE = -I $(HOME)/.brew/opt/readline/include

# INCLUDE para 42_rosana:
#INCLUDE = -I /System/Volumes/Data/sgoinfre/goinfre/Perso/roruiz-v/homebrew/opt/readline/include

# INCLUDE para casa_rosana:
#INCLUDE = -I/usr/local/opt/readline/include

SRC		=	main.c \
			lexer.c lexer_split.c lexer_utils.c lexer_split_qt.c \
			lexer_count_utils.c parser.c parser_errors.c parser_naming.c \
			lexer_count.c parser_list_redir.c \
			parser_utils.c parser_list.c parser_syntax.c parser_expander.c \
			parser_cleaner.c parser_utils2.c \
			msh_signals.c \
			msh_executor.c \
			msh_builtin_executor.c \
			msh_builtin_echo.c \
			msh_builtin_exit.c \
			msh_builtin_export.c \
			msh_builtin_cd.c \
			msh_builtin_cd_movements.c \
			msh_builtins_env_pwd_unset.c \
			msh_redir_heredoc.c \
			msh_redir_in_out_file.c \
			msh_env_lst_utils_dupl_env.c \
			msh_env_lst_utils_add_nds.c \
			msh_env_lst_utils_mfy_nds.c \
			msh_env_lst_utils_del_nds.c \
			msh_env_lst_utils_print_nds.c \
			msh_export_index_lst_creation.c \
			msh_export_index_lstadd_node.c \
			msh_get_cmd_path.c \
			msh_exec_external_cmd.c \
			msh_cmd_lst_utils_del_list.c \
			msh_utils.c	\
			msh_errors.c \
			msh_errors_start_and_signals.c

OBJS	= $(SRC:.c=.o)
OFILES = $(addprefix obj/, $(OBJS))

CC		= gcc

FLAGS	= -Wall -Werror -Wextra -g #-fsanitize=address

# juan-aga memory-leaks tool:
#LEAKS = memory-leaks/memory_leaks.a

LIBFT_PATH = libft/libft.a

all:	$(NAME)

#	We cannot call (LIBFT) or (MLX42) in (NAME) because it would be searching for the
#	".a" files before creating them, resulting in an error. We 1st create the rules to
#	compile both libft and MLX42, and then we compile the .a files of both libraries
#	with the apropiate flags and frameworks.

$(NAME): $(OFILES) $(LIBFT_PATH)
		$(CC) $(FLAGS) $(LIB) $(OFILES) $(LIBFT_PATH) -o $(NAME)
		clear
		
$(OFILES): $(SRC)
		@mkdir -p obj/
		$(CC) $(FLAGS) $(INCLUDE) -c $(SRC)
		@mv *.o obj/

$(LIBFT_PATH):
		make -C libft all

# If a debug with lldb is needed, do 'make' with this rule:
debug: $(LIBFT_PATH)
		$(CC) $(FLAGS) $(SRC) $(LIBFT_PATH) -o $(NAME) -g
		clear

clean:
		rm -rf obj
		make -C libft clean

fclean: clean
		@make fclean -C libft/
		@rm $(NAME)

re:	fclean all

.PHONY: all clean fclean re
