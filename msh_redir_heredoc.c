/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:40:41 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/01/23 15:22:55 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param data 
 * @param cmd_nd 
 * @param hd_inputs 
 */
static void	ft_redic_heredoc_to_pipe(t_msh *data, t_cmd *cmd_nd, char *hd_inputs)
{
	int	exit_code;

	exit_code = 0;
	cmd_nd->pipe_val = pipe(cmd_nd->fd);
	if (cmd_nd->pipe_val < 0)
		ft_error_pipes_forks(data, ERROR_PIPE_CREATION);
	cmd_nd->pid = fork();
	if (cmd_nd->pid < 0)
		ft_error_pipes_forks(data, ERROR_PID);
	else if (cmd_nd->pid == 0)
	{
		close(cmd_nd->fd[RD]);
		dup2(cmd_nd->fd[WR], STDOUT_FILENO);
		close(cmd_nd->fd[WR]);
		ft_putstr_fd(hd_inputs, STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(cmd_nd->fd[WR]);
		dup2(cmd_nd->fd[RD], STDIN_FILENO);
		close(cmd_nd->fd[RD]);
		waitpid(cmd_nd->pid, &exit_code, 0);
		data->exit_code = WEXITSTATUS(exit_code);
	}
}

/**
 * @brief 
 *  A heredoc is a redirection from a file descriptor to a pipe.
 *  It's principal characteristic is that restarts the stdin to keyboard,
 *   ignoring the pipe between the commands.
 * 
 *  A STDIN heredoc is always the keyboard, so we must restore the original
 *   stdin to avoid the heredoc to read from any other fd.
 *  A STDOUT heredoc is always the screen, so we must restore the original
 *   stdout to avoid the heredoc to write to any pipe and exit the pipeline.
 *   So, we must save the original stdin and stdout before calling 
 *   ft_redir_heredoc and restore (only the stdout) inmediately after.
 * 
 * @param data 
 * @param cmd_nd 
 * @param rd_nd 
 */
void	ft_redir_heredoc(t_msh *data, t_cmd *cmd_nd, t_rd *rd_nd)
{
	char	*input;
	int		extern_stdout;

	input = NULL;
	dup2(data->org_stdin, STDIN_FILENO);
	extern_stdout = dup(STDOUT_FILENO);
	dup2(data->org_stdout, STDOUT_FILENO);
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, rd_nd->endkey) == 0)
			break ;
		if (g_listen == 1)
			return ;
		rd_nd->heredoc = ft_join_free(rd_nd->heredoc, input);
		rd_nd->heredoc = ft_join_free(rd_nd->heredoc, "\n");
		ft_free_null_void_return(&input);
	}
	ft_free_null_void_return(&input);
	ft_redic_heredoc_to_pipe(data, cmd_nd, rd_nd->heredoc);
	dup2(extern_stdout, STDOUT_FILENO);
	close(extern_stdout);
	if (data->exit_code != 0)
		data->error = END;
}
