/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:55:03 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/10 18:09:15 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * -> parser must bring expanded vars to append at the end of a existing var
 *            ('ft_env_modify_or_add_node' makes the join job)
 * @param data 
 */
void	ft_builtin_export(t_msh *data, t_cmd *cmd_nd)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	if (ft_matrix_len(cmd_nd->c_args) == 1)
		ft_export_lst_print(data);
	else
	{
		while (cmd_nd->c_args[++i])
		{
			tmp = ft_2rows_split(cmd_nd->c_args[i], '=');
			if (ft_strchr(cmd_nd->c_args[i], '='))
				ft_env_modify_or_add_node(data, ft_env_lst_new(data, tmp, 1));
			else
				ft_env_modify_or_add_node(data, ft_env_lst_new(data, tmp, 0));
			ft_freedom(tmp);
		}
	}
}
