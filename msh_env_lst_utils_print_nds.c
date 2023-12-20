/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_print_nds.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:59:38 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/02 20:07:23 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief    
 * 
 *  ***  IT IS CALLED BY COMMAND "ENV" (without argmts)  ***
 * 	***    Only prints the node if its ->val != NULL     ***
 */
void	ft_env_lst_print(t_msh *data)
{
	t_env_lst *ptr;

	ptr = data->env_lst;
	while (ptr != NULL)
	{
		if (ptr->equal)
		{
			ft_putstr_fd(ptr->nm, data->fd);
			ft_putchar_fd('=', data->fd);
			ft_putstr_fd(ptr->val, data->fd);
			ft_putchar_fd('\n', data->fd);
		}
		ptr = ptr->nx;
	}
}

/**
 * @brief    *******  ORDENA lexicograficamente  *******
 * 
 *  ***   IT IS CALLED BY COMMAND "EXPORT" (without argmts)  ***
 * 	***         Prints all the nodes, in ascii order         ***
 */
void	ft_export_lst_print(t_msh *data)
{
	t_env_lst *index;
	t_env_lst *ptr;

	index = ft_index_built_lst(data);
	ptr = index;
	while (ptr != NULL)
	{
		ft_putstr_fd("declare -x ", data->fd);
		ft_putstr_fd(ptr->nm, data->fd);
		if (ptr->equal)
		{
			ft_putstr_fd("=\"", data->fd);
			ft_putstr_fd(ptr->val, data->fd);
			ft_putstr_fd("\"", data->fd);			
		}
		ft_putstr_fd("\n", data->fd);			
		ptr = ptr->nx;
	}
	ft_env_lstclear(index);
}
