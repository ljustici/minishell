/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:26:43 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/01/23 19:23:20 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief ** EXECUTE the pre-waitpid child TASKS: **
 * 
 * - 1st closes RD of current pipe (from here to right)
 * - 2nd reassigns as STDOUT the WR of current pipe (from here to right)
 * - 3rd closes (freeing) WR extreme of the pipe to the right
 * - 4th if there's an previous pipe (so it's not the 1st nor the last),
 * 	 reassings its RD extreme as STDIN
 * 
 * @param cmd_nd 
 * @param cmd_nd_prev 
 */
static void	ft_exec_change_fd_child(t_cmd *cmd_nd, t_cmd *cmd_nd_prev)
{
	close(cmd_nd->fd[RD]);
	dup2(cmd_nd->fd[WR], STDOUT_FILENO);
	close(cmd_nd->fd[WR]);
	if (cmd_nd_prev != NULL)
	{
		dup2(cmd_nd_prev->fd[RD], STDIN_FILENO);
		close(cmd_nd_prev->fd[RD]);
	}
}

/**	
 * @brief   ** EXECUTE the pre-waitpid parent TASKS: **
 * 
 * - 1st closes WR of current pipe (from here to the right)
 * - 2nd reassigns as STDIN the RD extreme of current pipe (to the right)
 *      (which will be closed in the next cmd loop)
 * 	    (child is who writes in the pipe to the right)
 * - 3rd closes (freeing) RD extreme of the pipe to the right
 *      (the number for fd asignations is free now to reuse)
 * 
 * @param cmd_nd 
 * @param cmd_nd_prev 
 */
static void	ft_exec_change_fd_parent(t_cmd *cmd_nd)
{
	close(cmd_nd->fd[WR]);
	dup2(cmd_nd->fd[RD], STDIN_FILENO);
	close(cmd_nd->fd[RD]); // esto queda cerrado por los restos (fd se reutiliza)
}

/**
 * @brief  ** EXECUTES THE PAIR OF CHILD & PARENT PROCESSES **
 * 
 * @param data 
 * @param cmd_nd 
 * @param cmd_nd_prev     used by child, not by parent
 */
static void	ft_chld_prn_routine(t_msh *d, t_cmd *cmd_nd, t_cmd *cmd_nd_prev)
{
	int	exit_code;

	if (d->m_pid == 0)
	{
		ft_exec_change_fd_child(cmd_nd, cmd_nd_prev);
		ft_builtin_executor(d, cmd_nd->c_args[0], cmd_nd);
		exit(d->exit_code);
	}
	else
	{
		ft_exec_change_fd_parent(cmd_nd);
		waitpid(d->m_pid, &exit_code, 0);
		d->exit_code = WEXITSTATUS(exit_code);
	}	
}

/**
 * @brief 	***  WE ARE HERE IF THERE'S MANY CMDs (some PIPES)    ***
 *          ***  but it works with only one command too           ***
 * 
 * 	- Parent creates the pipes in 1 by 1 & waits the execution of each child
 * 	- Children execute every cmd (unless the last one) sequentially
 * 	- Parent executes the last cmd at the end, outside the loop,
 *         & closes the read extreme of the pipe to the left
 * 	       (it can be the 1st cmd or an intermediate one)
 * @param data 
 */
static void	ft_exec_many_cmds(t_msh *data, t_cmd *cmd_nd, t_cmd *cmd_nd_prev)
{
	while (cmd_nd->nx != NULL)
	{
		data->m_pipe_val = pipe(cmd_nd->fd);
		if (data->m_pipe_val < 0)
		{
			ft_error_pipes_forks(data, ERROR_PIPE_CREATION);
			break ;
		}
		data->m_pid = fork();
		if (data->m_pid < 0)
		{
			ft_error_pipes_forks(data, ERROR_PID);
			break ;
		}
		ft_chld_prn_routine(data, cmd_nd, cmd_nd_prev);
		cmd_nd_prev = cmd_nd;
		cmd_nd = cmd_nd->nx;
	}
	if (data->error != END)
		ft_builtin_executor(data, cmd_nd->c_args[0], cmd_nd);
}

/**
 * @brief   
 *   It declares 2 pointers to the cmd list:
 * 		- first one is to point the head of the list
 * 		- the other one is to do the walk across the cmd list and preserve
 * 			a pointer to the previous node to become old fds closed
 *
 * @param data 
 */
void	ft_executor(t_msh *data)
{
	t_cmd	*cmd_nd;
	t_cmd	*cmd_nd_prev;

	cmd_nd = data->cmd_lst;
	cmd_nd_prev = NULL;
	ft_exec_many_cmds(data, cmd_nd, cmd_nd_prev);
}
