/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:02:03 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/10 14:57:16 by ljustici         ###   ########.fr       */
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

typedef struct s_cmd
{
	t_error	error;
	char	*path;
	int		num_args;
	char	**args;
} 			t_cmd;

typedef struct s_list_cmd
{
	t_error	error;
	int		num_cmds;
	t_cmd	**cmds;
	char	*outfile;
	char	*infile;
	int		num_pipes;
	int		*pipes;
}			t_list_cmd;

char	*find_path_in_envp(char **envp);
int		ft_array_len (char **array);
char	**get_all_paths(char *path);
char	*find_correct_path(char **paths, char *cmd);

#endif