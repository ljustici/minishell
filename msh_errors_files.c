/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:49:54 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/11 14:50:01 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_files(t_msh *data, t_cmd *cmd_nd, t_rd *rd_nd, int error)
{
	if (error == ERROR_OPEN_INFILE)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(rd_nd->file, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		data->exit_code = 1;
	}
	else if (error == ERROR_OPEN_OUTFILE)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(" : Permission denied\n", 2);
		data->exit_code = 1;
	}
	else if (error == ERROR_NO_SUCH_FILE_OR_DIRECTORY)
	{
		if (ft_strcmp(cmd_nd->c_args[0], "env") != 0)
			ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(cmd_nd->c_args[0], 2);
		ft_putstr_fd(": ", 2);
		if (cmd_nd->c_args[1])
			ft_putstr_fd(cmd_nd->c_args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->exit_code = 127;
		data->error = NO_ERROR;
	}
}
