/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:02:03 by ljustici          #+#    #+#             */
/*   Updated: 2023/12/18 18:39:40 by ljustici         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

#define WORD = 1;
#define FLAG = 2;

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

	ERROR_SYNTAX_UNEXPECTED_TOKEN,
}	t_error;

typedef struct s_token
{
	char	**tokens;
	const char *s;
	int			q;
}			t_lexer;

typedef struct s_rd
{
	int type;
	char *file;
	char *heredoc;
	char *endkey;
	struct s_rd *next;
}			t_rd;


typedef struct	s_cmd
{
	int					type;        // 0 = cmd; 1 = redirecmto
	char				**c_args;	 // cmd[0] + argmts & flags of the command
	char				*c_abs_path; // absolute direction & command
	char				*c_env_path; // path (from $PATH) & command
	int					pid;
	int					fd[2];
	struct s_rd			*rds;
	struct s_msh		*orgn;       // redirección a la struct ppal
	struct s_cmd	*next;
}			t_cmd;

typedef	struct s_env_lst
{
	char				*nm;
	char				*val;
	int					equal;
	struct s_env_lst	*nx;
}			t_env_lst;

//Lexer

int	count_tokens(const char *str);
char **split_line(char *line);
char **split_by_metachar (char const *s);
int should_split(char c);

void span_until_quote(const char *s, unsigned long *i, char quote);
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

int assign_var_token(t_lexer lex, size_t *i, int *j, int f_letter_pos);

int is_equal_after_var(const char *s, unsigned long pos);

int is_first_quote(const char *s, unsigned long pos, char c);

char	*ft_join_free(char *s1, char *s2);


//Parser

int is_word(char *token);
int is_flag(char *token);
int is_redir(char *token);
int is_pipe(char *token);
int set_token_type(char *token);
char *clean_quotes(char *s, char q);
int is_special_cmd_chars(char *token);
char **parse_token_array(char **tokens);
int has_qts(char *token, char q);
void	error_syntax_token(char *token, int error);
int	ft_array_len(char **str);
int is_var(char *token);
void	create_list(t_cmd **list, char **tokens, int n);
void ft_parse(char **tokens, t_env_lst *envp);
int check_token_syntax(char **tokens);
char **expanding_loop(char **tokens, t_env_lst *envp);

int contains_var(char *token);
size_t get_end_of_var(char *token);
char *format_expansion_token(char *token, char *expanded, size_t end, int start);

int set_redir_type(char *token);

#endif