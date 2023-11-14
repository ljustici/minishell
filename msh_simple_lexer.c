/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_simple_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:39:26 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/14 13:57:17 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	ft_cmd_lstadd_back(t_msh *data, t_cmd_lst *new)
{
	t_cmd_lst	*tmp;

	tmp = NULL;
	if (data->cmd_lst == NULL && new)
		data->cmd_lst = new;
	else if (data->cmd_lst && new)
	{
		tmp = data->cmd_lst;
		while (tmp->nx && tmp->nx->nx)
			tmp = tmp->nx;
		new->nx = tmp->nx;
		tmp->nx = new;
	}
} */

static t_cmd_lst	*ft_cmd_lst_new(t_msh *data, char **cmd)
{
	t_cmd_lst	*node;
	int			i;

	(void)data;
	i = -1;
	node = (t_cmd_lst *)malloc(sizeof(t_cmd_lst));
	node->c_args = ft_calloc((ft_matrix_len(cmd) + 1), sizeof(char *));
	while (cmd[++i])
		node->c_args[i] = ft_strdup(cmd[i]);
	node->c_abs_path = ft_strdup(cmd[0]);
//	node->env_path = ft_find_path(data, node->cmd_args[0]);
	node->c_env_path = NULL;
	node->nx = NULL;
	ft_freedom(cmd);
	return (node);
}

/**
 * @brief 		*****     BEWARE OF THIS !!!!!!   *****
 * 	   This is a false lexer, it's only a practical way to test things
 * 
 * @param data 
 * @param pipeline 
 */
void	ft_simple_lexer(t_msh *data)
{
	char	**cmd;
	int		i;
	
	i = -1;
	cmd = NULL;
	cmd = ft_split(data->pipeline, ' ');
	if (ft_matrix_len(cmd) == 0) // cd en pipeline solo hay espacios en blanco
	{
		ft_freedom(cmd);
		data->error = ERROR_ARGMTS;
		return ;
	}
	ft_msh_lstadd_front(data, ft_cmd_lst_new(data, cmd), 2);
//	ft_cmd_lstadd_back(data, ft_cmd_lst_new(data, cmd));
}
