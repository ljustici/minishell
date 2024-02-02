/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:21:55 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/01 16:38:24 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * Each command has one redirs linked list:
 * 	- every redir node will change the command STDIN/STDOUT
 *  - so, only the last redir of each STDIN/STDOUT natu, finally defines
 *    the definitely in/out of its command 
 * 
 * @param data 
 * @param cmd_nd 
 */
static void	ft_redir_checker(t_msh *data, t_cmd *cmd_nd)
{
	t_rd	*rd_nd;

	rd_nd = cmd_nd->rds;
	while (rd_nd != NULL)
	{
		if (cmd_nd->rds != NULL && rd_nd->type == DIR)
			ft_redir_heredoc(data, cmd_nd, rd_nd);
		else if (cmd_nd->rds != NULL && rd_nd->type == SIR)
			ft_redir_infile(data, cmd_nd, rd_nd);
		else if (cmd_nd->rds != NULL && rd_nd->type == SOR)
			ft_redir_outfile(data, cmd_nd, rd_nd);
		else if (cmd_nd->rds != NULL && rd_nd->type == DOR)
			ft_redir_outfile(data, cmd_nd, rd_nd);
		rd_nd = rd_nd->nx;
	}
}

static void	ft_cmd_analyzer(t_msh *data, char *cmd, t_cmd *cmd_nd)
{
	if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "ENV") == 0)
		ft_builtin_env(data, cmd_nd);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_builtin_export(data, cmd_nd);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_builtin_unset(data, cmd_nd);
	else if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD") == 0)
		ft_builtin_pwd(data);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_builtin_cd(data, cmd_nd);
	else if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "ECHO") == 0)
		ft_builtin_echo(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_builtin_exit(data, cmd_nd);
	else
	{
		ft_find_cmd_path(cmd_nd, ft_find_env_paths(data));
		data->exit_code = ft_exec_external_cmd(data, cmd_nd);
	}
}

/**
 * @brief 
 * 
 * 	>> env    -> bash admits both LOWERS & UPPERS
 *  >> export -> bash admits only LOWERS, not UPPERS
 *  >> unset  -> bash admits only LOWERS, not UPPERS
 *  >> pwd    -> bash admits both LOWERS & UPPERS
 *  >> cd     -> bash admits both LOWERS & UPPERS (but do nothing if UPPERS)
 *  >> echo   -> bash admits both LOWERS & UPPERS
 *  >> exit   -> bash admits only LOWERS, not UPPERS
 * 
 * @param data 
 * @param cmd 
 * @param tmp 
 */
void	ft_builtin_executor(t_msh *data, char *cmd, t_cmd *cmd_nd)
{
	if (cmd_nd->rds != NULL)
	{
		ft_redir_checker(data, cmd_nd);
		if (g_listen == 1 || data->error != NO_ERROR)
			return ;
	}
	if (!cmd)
		return ;
	ft_cmd_analyzer(data, cmd, cmd_nd);
}
