/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_in_out_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:40:27 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/01 21:47:27 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief
 * 
 *   my first line -> close(cmd_nd->fd[RD]); // BAD FD ERROR, has been deleted
 *      // to close the possible previous fd open by a pipe
 * @param data 
 * @param cmd_nd 
 * @param rd_nd 
 */
void	ft_redir_infile(t_msh *data, t_cmd *cmd_nd, t_rd *rd_nd)
{
	cmd_nd->fd[RD] = open(rd_nd->file, O_RDONLY);
	if (cmd_nd->fd[RD] < 0)
	{
		data->error = ERROR_OPEN_INFILE;
		ft_error_files(data, cmd_nd, rd_nd, data->error);
	}
	else
	{
		dup2(cmd_nd->fd[RD], STDIN_FILENO);
		close(cmd_nd->fd[RD]);
	}
}

void	ft_redir_outfile(t_msh *data, t_cmd *cmd_nd, t_rd *rd_nd)
{
	if (rd_nd->type == SOR)
	{
		close(cmd_nd->fd[WR]);
		cmd_nd->fd[WR] = open(rd_nd->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	else if (rd_nd->type == DOR)
	{
		close(cmd_nd->fd[WR]);
		cmd_nd->fd[WR] = open(rd_nd->file, O_CREAT | O_APPEND | O_RDWR, 0644);
	}
	if (cmd_nd->fd[WR] < 0)
	{
		data->error = ERROR_OPEN_OUTFILE;
		ft_error_files(data, cmd_nd, rd_nd, data->error);
	}
	else
	{
		dup2(cmd_nd->fd[WR], STDOUT_FILENO);
		close(cmd_nd->fd[WR]);
	}
}
