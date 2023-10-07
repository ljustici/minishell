/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:02:03 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/07 15:50:20 by ljustici         ###   ########.fr       */
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

typedef struct s_error
{
	
}	t_error;

typedef struct s_cmd
{
	t_error	error;
	int		*fd;
	char	**cmd_args;
	char	**cmd_path;
	char	*env_path;
	int		n_cmd;
} 			t_cmd;

char	*find_path_in_envp(char **envp);
int		ft_array_len (char **array);
char	**get_all_paths(char *path);
char	*find_correct_path(char **paths, char *cmd);

#endif