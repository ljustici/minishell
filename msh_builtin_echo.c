/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:57:12 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/13 20:59:07 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   ** THIS IS ONLY A SIMPLE VERSION TO CHECK EXIT_STATUS **
 * 	(The definitive versión is being builting by @ljustici - ADA)
 * 
 * @param data 
 */
void	ft_builtin_echo(t_msh *data)
{ // ADMITS OPTION -n & ARGMTS
	if (ft_strcmp(data->cmd_lst->c_args[1], "$?") == 0)
	{
		ft_putstr_fd(ft_itoa(data->exit_code), data->fd);
		ft_putchar_fd('\n', data->fd);
		data->exit_code = 0;
	}
}
