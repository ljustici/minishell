/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_in_out_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:40:27 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/17 12:55:47 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_infile(t_msh *data, t_cmd *cmd_nd, t_rd *rd_nd)
{
	(void)data;

//	cmd_nd->fd_in = open(rd_nd->file, O_RDONLY);
	close(cmd_nd->fd[RD]); // si hay pipe, cierro el que se asignó al pipe
	cmd_nd->fd[RD] = open(rd_nd->file, O_RDONLY);
//	if (cmd_nd->fd_in < 0)
	if (cmd_nd->fd[RD] < 0)
	{
		data->error = ERROR_OPEN_INFILE;
		ft_error_files(data, cmd_nd, rd_nd, data->error);
	}
	else
	{
//		dup2(cmd_nd->fd_in, STDIN_FILENO);
		dup2(cmd_nd->fd[RD], STDIN_FILENO);
//		close(cmd_nd->fd_in);
		close(cmd_nd->fd[RD]);
	}
}

void	ft_redir_outfile(t_msh *data, t_cmd *cmd_nd, t_rd *rd_nd)
{
	(void)data;

	if (rd_nd->type == SOR)
	{
		printf("DEBUG: ft_redir_outfile) SOR - file = %s\n", rd_nd->file);	
//		cmd_nd->fd_out = open(rd_nd->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		close(cmd_nd->fd[WR]); // si hay pipe, cierro el que se asignó al pipe
		cmd_nd->fd[WR] = open(rd_nd->file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	else if (rd_nd->type == DOR)
	{
		printf("DEBUG: ft_redir_outfile) DOR - file = %s\n", rd_nd->file);	
//		cmd_nd->fd_out = open(rd_nd->file, O_CREAT | O_APPEND | O_RDWR, 0644);
		close(cmd_nd->fd[WR]); // si hay pipe, cierro el que se asignó al pipe
		cmd_nd->fd[WR] = open(rd_nd->file, O_CREAT | O_APPEND | O_RDWR, 0644);
	}
//	if (cmd_nd->fd_out < 0)
	if (cmd_nd->fd[WR] < 0)
	{
		data->error = ERROR_OPEN_OUTFILE;
		ft_error_files(data, cmd_nd, rd_nd, data->error);
	}
	else
	{
//		dup2(cmd_nd->fd_out, STDOUT_FILENO);
		dup2(cmd_nd->fd[WR], STDOUT_FILENO);
//		close(cmd_nd->fd_out);
		close(cmd_nd->fd[WR]);
	}
}
