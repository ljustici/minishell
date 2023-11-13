/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:02:03 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/13 16:09:01 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ENV_PATH "PATH="
# define READ_END 0
# define WRITE_END 1

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef enum e_error
{
	NO_ERROR,
	ERROR_ARGMTS,
	ERROR_INFILE,
	ERROR_OUTFILE,
	ERROR_FILES_FD,
	ERROR_PIPE,
	ERROR_PID_1,
	ERROR_PID_2,
	ERROR_CMD_1_NOT_EXISTS,
	ERROR_CMD_2_NOT_EXISTS,
	ERROR_SPLIT_EXTRACTING_CMD = 20, // be free!
}	t_error;

enum	metachar
{
	NEWLINE = '\n',
	TAB = '\t',
	SPACE = ' ',
	PIPE = '|',
	SEMI = ';',
};

typedef struct s_token
{
	char	**tokens;
	const char *s;
}			t_lexer;



char **split_line(char *line);
char **split_by_metachar (char const *s);
int should_split(char c);

void span_until_quote(const char *s, unsigned long *i, char quote);
int should_split(char c);
int is_metacharacter(char c);
int is_spnltab(char c);

int assign_doubleqt_token(t_lexer lex, size_t *i, int *j, int f_letter_pos);
int assign_quoted_token(t_lexer lex, size_t *i, int *j, int f_letter_pos);

int is_var_in_dqt(const char *s, unsigned long pos);

int handle_count_quote(const char *str, unsigned long *j, int *i);
void span_tail_str(const char *str, unsigned long *j);
int add_token(t_lexer lex, int f_letter_pos, size_t i, int *j);
void span_var_in_dqt(const char *s, size_t *i, size_t end_qt);
int get_char_pos(const char *s, size_t start, char c);

#endif