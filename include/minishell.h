/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:02:03 by ljustici          #+#    #+#             */
/*   Updated: 2023/12/20 16:35:14 by ljustici         ###   ########.fr       */
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
	ERROR_SIGACTION_FAILURE,
	ERROR_ARGMTS,
	ERROR_INFILE,
	ERROR_OUTFILE,
	ERROR_FILES_FD,
	ERROR_OPEN_INFILE,
	ERROR_OPEN_OUTFILE,
	ERROR_PIPE_CREATION,
	ERROR_PIPE_EXECUTION,
	ERROR_PID,
	ERROR_NO_PATHS,
	ERROR_CMD_NOT_EXISTS,
	ERROR_CMD_NOT_EXECUTABLE,
	ERROR_CHDIR_FAILURE,
	ERROR_CHDIR_OLDPWD_NOT_SET,
	ERROR_CHDIR_HOME_NOT_SET,
	ERROR_TOO_MANY_ARGUMENTS,
	ERROR_NO_SUCH_FILE_OR_DIRECTORY,
	ERROR_START_NO_SUCH_FILE_OR_DIRECTORY,
	ERROR_SPLIT_EXTRACTING_CMD,
	

	ERROR_SYNTAX_UNEXPECTED_TOKEN,
	ERROR_QUOTE,
	ERROR_MALLOC_ERROR,

	END = 99,
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
	struct s_rd *nx;
}			t_rd;


typedef struct	s_cmd_lst
{
	t_rd				*rds;
	char				**c_args;
	char				*c_abs_path;
	char				*c_env_path;
	int					pid;		// used by ft_builtin || ft_exec_external_cmd
	int					pipe_val;	// exclusive used by ft_heredoc (usa pipe)
	int					fd[2];		// used for all processes and redirs
//	int					fd_in;		// exclusive used by ft_redirs (if exists, close fd[0])
//	int					fd_out;		// exclusive used by ft_redirs (if exists, close fd[1])
	struct s_msh		*orgn;
	struct s_cmd_lst	*nx;
}						t_cmd;

typedef	struct s_env_lst
{
	char				*nm;
	char				*val;
	int					equal;
	struct s_env_lst	*nx;
}			t_env_lst;

typedef struct	s_msh
{
	struct sigaction	sig;
	char				*var_; // para el '$_' que falta implementar
	t_error				error;
	t_env_lst			*env_lst;
	t_cmd				*cmd_lst;
	char				*pipeline;
	int					m_pid;		// used by ft_execute_many_cmds
	int					m_pipe_val;	// used by ft_execute_many_cmds
	int					fd;			// now it's used by many parts of msh, REVISAR !!!!!
	int					org_stdin;	// to keep the original STDIN
	int					org_stdout; // to keep the original STDOUT
	int					exit_code;
}						t_msh;

//Lexer

int	count_tokens(const char *str);
char **split_line(char *line, t_msh *data);
char **split_by_metachar (char const *s, t_msh *data);
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

void ft_lexer(t_msh *data);

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
void	error_syntax_token(t_msh *data, char *token, int error);
int	ft_array_len(char **str);
int is_var(char *token);
void	create_list(t_cmd **list, char **tokens, int n);
void ft_parse(char **tokens, t_msh *data);
int check_token_syntax(char **tokens);
char **expanding_loop(char **tokens, t_env_lst *envp);

int contains_var(char *token);
size_t get_end_of_var(char *token);
char *format_expansion_token(char *token, char *expanded, size_t end, int start);

int set_redir_type(char *token);


/* ***************************************************************** */
/* ******************      SIGNAL  FUNCTIONS       ***************** */
/* ***************************************************************** */

void	ft_handler(int sig, siginfo_t *info, void *context);
void	ft_ctrl_d(t_msh *data);

/* ***************************************************************** */
/* *****************     ENVIRONMENT  FUNCTIONS    ***************** */
/* ********     will be used by [env], [export], [unset]    ******** */
/* ***************************************************************** */

void		ft_duplic_envp(t_msh *data, char **envp);
void		ft_env_exchange_val(t_env_lst *t_nd, t_env_lst *new);
t_env_lst	*ft_env_lst_new(char **tmp_env, int equal);
void		ft_env_join_val(t_env_lst *t_nd, t_env_lst *new);
void		ft_env_modify_or_add_node(t_msh *data, t_env_lst *new);
void		ft_env_lstadd_back(t_msh *data, t_env_lst *new);
void		ft_msh_lstadd_front(t_msh *data, void *new, int type);
void		ft_env_lstclear(t_env_lst *del_lst);
void		ft_env_lstdelone(t_msh *data, char *del_env_nm);
void		ft_env_lst_print(t_msh *data);
void		ft_export_lst_print(t_msh *data);
void		ft_free_envlst_node(t_env_lst *del_node);
t_env_lst	*ft_index_built_lst(t_msh *data);
t_env_lst	*ft_index_new_nd(t_env_lst *nd);
void		*ft_index_lstadd_back(t_env_lst *index, t_env_lst *nd);
t_env_lst	*ft_index_lstadd_front(t_env_lst *index, t_env_lst *nd);
void		ft_index_lstadd_mid(t_env_lst *prev, t_env_lst *nd);
char		**ft_find_env_paths(t_msh *data);
int			ft_env_lst_count_nds(t_env_lst *env_lst);

/* ***************************************************************** */
/* *********     false LEXER & PARSER  FUNCTIONS      ************** */
/* ***************************************************************** */

void	ft_init_msh_struct(t_msh *data);
void	ft_simple_lexer(t_msh *data);
void	ft_simple_parser(t_msh *data);
int		ft_env_forbidden_chars(char *name);

/* ***************************************************************** */
/* ******************     CMD LIST  FUNCTIONS      ***************** */
/* ***************************************************************** */

void	ft_cmdclear(t_msh *data);

/* ***************************************************************** */
/* ***************        EXECUTOR  FUNCTIONS         ************** */
/* ***************************************************************** */

void	ft_executor(t_msh *data);
void	ft_redir_heredoc(t_msh *data, t_cmd *cmd_nd, t_rd *rd_nd);
void	ft_redir_infile(t_msh *data, t_cmd *cmd_nd, t_rd *rd_nd);
void	ft_redir_outfile(t_msh *data, t_cmd *cmd_nd, t_rd *rd_nd);
void	ft_builtin_executor(t_msh *data, char *cmd, t_cmd *cmd_nd);

/* ***************************************************************** */
/* ******************     BUILTINS  FUNCTIONS      ***************** */
/* ***************************************************************** */

void	ft_builtin_echo(t_msh *data);
void	ft_builtin_exit(t_msh *data, t_cmd *cmd_nd);
void	ft_builtin_env(t_msh *data, t_cmd *cmd_nd);
void	ft_builtin_export(t_msh *data, t_cmd *cmd_nd);
void	ft_builtin_pwd(t_msh *data);
void	ft_builtin_unset(t_msh *data, t_cmd *cmd_nd);
void	ft_builtin_cd(t_msh *data, t_cmd *cmd_nd);
void	ft_builtin_cd_down(t_msh *data, t_cmd *cmd_nd);
void	ft_builtin_cd_without_args(t_msh *data, t_cmd *cmd_nd, int exit_code);
void	ft_builtin_cd_oldpwd(t_msh *data, t_cmd *cmd_nd);
void	ft_env_change_val(t_msh *data, char *nm_dst, char *new_val);
char	*ft_env_obtain_val(t_msh *data, char *env_nm);

/* ***************************************************************** */
/* ****************     EXTERNAL CMDS  FUNCTIONS     *************** */
/* ***************************************************************** */

void	ft_find_cmd_path(t_cmd *cmd, char **paths);
int		ft_exec_external_cmd(t_msh *data, t_cmd *cmd_nd);

/* ***************************************************************** */
/* ********************     ERROR  FUNCTIONS     ******************* */
/* ***************************************************************** */

void	ft_error_start(char *argv_1, int error);
void	ft_error_status(t_msh *data, t_cmd *cmd_nd, int error);
void	ft_error_signal(int error);
void	ft_error_cd(t_msh *data, t_cmd *cmd_nd, int error);
void	ft_error_pipes_forks(t_msh *data, int error);
//void	ft_error_files(t_msh *data, t_cmd *cmd_nd, int error);
void	ft_error_files(t_msh *data, t_cmd *cmd_nd, t_rd *rd_nd, int error);

/* ***************************************************************** */
/* ********************     UTILS  FUNCTIONS     ******************* */
/* ***************************************************************** */

void	ft_free_null_void_return(char **str);
char	*ft_free_null_no_void_return(char *str);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
int		ft_str_equal(char *s1, char *s2);
char	**ft_2rows_split(char *str, char c);
int		ft_matrix_len(char **str);
int		ft_is_str_digits(char *str);

#endif