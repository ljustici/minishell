/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins_env_pwd_unset.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:02:24 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/17 12:55:47 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief      ****       ENV without argmts       ****
 *   Checks if there is any argmts (& displays error in that case)
 * @param data 
 */
void	ft_builtin_env(t_msh *data, t_cmd *cmd_nd)
{
	if (ft_matrix_len(cmd_nd->c_args) == 1)
		ft_env_lst_print(data);
	else
		ft_error_files(data, cmd_nd, NULL, ERROR_NO_SUCH_FILE_OR_DIRECTORY);
}

/**
 * @brief   **  UNSET admits many argmts (many env vars to delete)  **
 * 
 * @param data 
 */
void	ft_builtin_unset(t_msh *data, t_cmd *cmd_nd)
{ // VERIFICAR EL CÓDIGO DE SALIDA
	int	i;

	i = 0;
	while (cmd_nd->c_args[++i])
		ft_env_lstdelone(data, cmd_nd->c_args[i]);
}

void	ft_builtin_pwd(t_msh *data)
{ // VERIFICAR EL CÓDIGO DE SALIDA
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, data->fd);
	ft_putchar_fd('\n', data->fd);
	ft_free_null_void_return(&cwd);
	data->exit_code = 0;
}
