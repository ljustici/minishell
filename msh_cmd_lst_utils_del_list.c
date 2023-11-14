/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cmd_lst_utils_del_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:06:59 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/10 20:26:46 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_cmdlst_node(t_cmd_lst *del_node)
{
	ft_freedom(del_node->c_args);
	ft_free_null_void_return(&del_node->c_abs_path);
	ft_free_null_void_return(&del_node->c_env_path);
	free(del_node);
	del_node = NULL;
}

void	ft_cmd_lstclear(t_msh *data)
{
	t_cmd_lst	*del_node;
	
	if (data->cmd_lst == NULL)
		return ;
	while (data->cmd_lst)
	{
		del_node = data->cmd_lst;
		data->cmd_lst = del_node->nx;
		ft_free_cmdlst_node(del_node);
	}	
}
