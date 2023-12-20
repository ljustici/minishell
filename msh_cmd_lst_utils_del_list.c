/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmd_lst_utils_del_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:06:59 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/20 12:57:37 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_rds_node(t_rd *rd_del)
{
	ft_free_null_void_return(&rd_del->end_key);
	ft_free_null_void_return(&rd_del->heredoc);
	ft_free_null_void_return(&rd_del->file);
	free(rd_del);
	rd_del = NULL;
}

static void	ft_rds_lstclear(t_cmd *del_node)
{
	t_rd	*rd_del;

	if (del_node->rds == NULL)
		return ;
	while (del_node->rds)
	{
		rd_del = del_node->rds;
		del_node->rds = rd_del->nx;
		ft_free_rds_node(rd_del);
	}
}

static void	ft_free_cmdlst_node(t_cmd *del_node)
{
	ft_rds_lstclear(del_node);
	ft_freedom(del_node->c_args);
//	ft_free_null_void_return(&del_node->c_abs_path);
	ft_free_null_void_return(&del_node->c_env_path);
	free(del_node);
	del_node = NULL;
}

void	ft_cmdclear(t_msh *data)
{
	t_cmd	*del_node;
	
	if (data->cmd_lst == NULL)
		return ;
	while (data->cmd_lst)
	{
		del_node = data->cmd_lst;
		data->cmd_lst = del_node->nx;
		ft_free_cmdlst_node(del_node);
	}	
}
