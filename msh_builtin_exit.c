/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:17:18 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/10 19:40:07 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_both_linked_lists(t_msh *data)
{
	ft_cmdclear(data);
	ft_env_lstclear(data->env_lst);
}

/**
 * @brief   ** RETURNS AN EXIT VALUE that DEPENDS ON SOME FACTS **
 * 
 *    Don't alterate the following order {'if / if else'}'s chain,
 *       (it's deeply thought to show the correct messages)
 *  for example: the last 'else' is an exit without arguments
 * 
 * @param data 
 */
void	ft_builtin_exit(t_msh *data, t_cmd *cmd_nd)
{
	ft_putstr_fd(cmd_nd->c_args[0], 1);
	ft_putchar_fd('\n', 1);
	if (ft_matrix_len(cmd_nd->c_args) > 1
		&& (!ft_is_str_digits(cmd_nd->c_args[1])))
	{
		ft_putstr_fd("msh: exit: ", 2);
		ft_putstr_fd(cmd_nd->c_args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_both_linked_lists(data);
		exit(255);
	}
	else if (ft_matrix_len(cmd_nd->c_args) > 2)
		ft_error_status(data, cmd_nd, ERROR_TOO_MANY_ARGUMENTS);
	else if (ft_matrix_len(cmd_nd->c_args) == 2
		&& ft_is_str_digits(cmd_nd->c_args[1]))
	{
		ft_env_lstclear(data->env_lst);
		exit(ft_atoi(cmd_nd->c_args[1]));
	}
	else
	{
		ft_free_both_linked_lists(data);
		exit(0);
	}
}
