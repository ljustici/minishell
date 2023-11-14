/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_external_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:15:50 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/13 19:46:11 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_lst_count_nds(t_env_lst *env_lst)
{ // FUNCIONA BIEN - OK
	int	elmts;
	t_env_lst *tmp;

	elmts = 0;
	tmp = env_lst;
	while (tmp != NULL)
	{
		elmts++;
		tmp = tmp->nx;
	}
	return (elmts);
}

static char	**ft_conv_envlst_to_mtrx(t_msh	*data)
{
	char		**my_envp;
	t_env_lst	*tmp;
	int			i;
	int			nb_env;

	i = 0;
	my_envp = NULL;
	nb_env = ft_env_lst_count_nds(data->env_lst);
	tmp = data->env_lst;
	my_envp = ft_calloc(nb_env + 1, sizeof(char *));
	while (tmp != NULL)
	{
		my_envp[i] = ft_strdup(tmp->nm);
		if (tmp->equal)
		{
			my_envp[i] = ft_join_free(my_envp[i], "=");
			my_envp[i] = ft_join_free(my_envp[i], tmp->val);
		}
		tmp = tmp->nx;
		i++;
	}
	return (my_envp);
}

int	ft_exec_external_cmd(t_msh *data)
{
	int		exit_code;
	char	**my_envp;

	exit_code = 0;
	my_envp = ft_conv_envlst_to_mtrx(data);
	data->cmd_lst->pid = fork();
	if (data->cmd_lst->pid == -1)
		ft_error_status(data, ERROR_PID);
	if (data->cmd_lst->pid == 0)
	{
		execve(data->cmd_lst->c_env_path, data->cmd_lst->c_args, my_envp);
		ft_error_status(data, ERROR_CMD_NOT_EXISTS);
	//	exit (127);
	}
	else
		waitpid(data->cmd_lst->pid, &exit_code, 0);
	ft_freedom(my_envp);
	return (WEXITSTATUS(exit_code));
}
