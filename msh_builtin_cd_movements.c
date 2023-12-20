/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_cd_movements.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 00:24:20 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/17 12:55:47 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   ** When 'cd' is followed by a word with no special chars **
 *     Then is needed to join the HOME path + '/' + word to go level down
 * @param data 
 */
void	ft_builtin_cd_down(t_msh *data, t_cmd *cmd_nd)
{
	char	*path;

	path = ft_join_free(ft_env_obtain_val(data, "PWD"), "/");
	path = ft_join_free(path, cmd_nd->c_args[1]);
	if (chdir(path) == 0)
	{
		ft_env_change_val(data, "OLDPWD", ft_env_obtain_val(data, "PWD"));
		ft_env_change_val(data, "PWD", getcwd(NULL, 0));
	}
	else
		ft_error_cd(data, cmd_nd, ERROR_CHDIR_FAILURE);
	ft_free_null_void_return(&path);
}

/**
 * @brief   *** When the command cd is written with no argmts  ***
 *               *** or it's followed by '~' character ***
 *                 Then, cd change to the HOME directory
 * @param data 
 */
void	ft_builtin_cd_without_args(t_msh *data, t_cmd *cmd_nd, int exit_code)
{
	char	*path;
	
	path = ft_env_obtain_val(data, "HOME");
	if (path == NULL)
	{
		ft_error_cd(data, cmd_nd, ERROR_CHDIR_HOME_NOT_SET);
		data->exit_code = exit_code;
		return ;
	}
	if (chdir(path) == 0)
	{
		ft_env_change_val(data, "OLDPWD", ft_env_obtain_val(data, "PWD"));
		ft_env_change_val(data, "PWD", getcwd(NULL, 0));
	}
	else
		ft_error_cd(data, cmd_nd, ERROR_CHDIR_FAILURE);
	ft_free_null_void_return(&path);
}

/**
 * @brief   ** When cd is followed by the '-' char  ** 
 *             Then, cd change to OLDPWD directory
 *             But 'chdir' don't do this change (returns FAILURE)
 *                 SO, IT'S NEEDED TO DO STEP BY STEP
 * 
 * @param data 
 */
void	ft_builtin_cd_oldpwd(t_msh *data, t_cmd *cmd_nd)
{
	char	*path;

	path = ft_env_obtain_val(data, "OLDPWD");
	if (path == NULL)
	{
		ft_error_cd(data, cmd_nd, ERROR_CHDIR_OLDPWD_NOT_SET);
		return ;
	}
	ft_printf("%s\n", path);
	if (chdir(path) == 0)
	{
		ft_env_change_val(data, "OLDPWD", ft_env_obtain_val(data, "PWD"));	
		ft_env_change_val(data, "PWD", getcwd(NULL, 0));
		data->exit_code = 0;
	}
	else
		ft_error_cd(data, cmd_nd, ERROR_CHDIR_FAILURE);
	ft_free_null_void_return(&path);
}
