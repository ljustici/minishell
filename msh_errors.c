/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:30:00 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/11 14:52:27 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_status(t_msh *data, t_cmd *cmd_nd, int error)
{
	if (error == END)
		data->error = END;
	else if (error == ERROR_NO_PATHS)
	{
		ft_putstr_fd("Error: PATH doesn't exist\n", 2);
		data->error = NO_ERROR;
	}
	else if (error == ERROR_CMD_NOT_EXISTS)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd_nd->c_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		data->error = NO_ERROR;
		data->exit_code = 127;
	}
	else if (error == ERROR_TOO_MANY_ARGUMENTS)
	{
		ft_putstr_fd("msh: exit: too many arguments\n", 2);
		data->exit_code = 1;
		data->error = NO_ERROR;
	}
}

void	ft_error_pipes_forks(t_msh *data, int error)
{
	if (error == ERROR_PID)
	{
		ft_putstr_fd("Error: PID\n", 2);
		data->error = END;
	}
	else if (error == ERROR_PIPE_CREATION)
	{
		ft_putstr_fd("Error: pipe \n", 2);
		data->error = END;
	}
	else if (error == ERROR_PIPE_EXECUTION)
	{
		ft_putstr_fd("Error: pipe execution command error\n", 2);
		data->error = END;
	}
}

void	ft_error_export(t_msh *data, char *nm, int error)
{
	if (error == ERROR_INVALID_EXPORT_IDENTIFIER)
	{
		ft_putstr("msh: export: `", 2);
		ft_putstr(nm, 2);
		ft_putstr("': not a valid identifier\n", 2);
		error = NO_ERROR;
		data->exit_code = 1;
	}
}

void	ft_error_cmds(t_msh *data, t_cmd *cmd_nd, int error)
{
	if (error == ERROR_CMD_NOT_EXISTS)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd_nd->c_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		data->exit_code = 127;
	}
	else if (error == ERROR_CMD_NOT_EXECUTABLE)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd_nd->c_args[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		data->exit_code = 126;
	}
	else if (error == ERROR_NO_PERMISSION)
	{
		ft_putstr_fd(cmd_nd->c_args[0], 2);
		ft_putstr_fd(": permission denied: ", 2);
		ft_putstr_fd("\n", 2);
		data->exit_code = 1;
	}
}
