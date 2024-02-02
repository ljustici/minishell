/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_print_nds.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:59:38 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/01 17:20:28 by roruiz-v         ###   ########.fr       */
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
	t_env_lst	*ptr;

	ptr = data->env_lst;
	while (ptr != NULL)
	{
		if (ptr->equal)
		{
			ft_putstr_fd(ptr->nm, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(ptr->val, 1);
			ft_putchar_fd('\n', 1);
		}
		ptr = ptr->nx;
	}
}

/**
 * @brief
 * 
 *  ***   IT IS CALLED BY COMMAND "EXPORT" (without argmts)  ***
 * 	***         Prints all the nodes, in ascii order         ***
 */
void	ft_export_lst_print(t_msh *data)
{
	t_env_lst	*index;
	t_env_lst	*ptr;

	index = ft_index_built_lst(data);
	ptr = index;
	while (ptr != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(ptr->nm, 1);
		if (ptr->equal)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(ptr->val, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		ptr = ptr->nx;
	}
	ft_env_lstclear(index);
}
