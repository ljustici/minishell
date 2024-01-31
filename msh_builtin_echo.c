/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:58:13 by ljustici          #+#    #+#             */
/*   Updated: 2024/01/31 19:03:32 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtin_echo(t_msh *data)
{
    t_cmd* list;
    int first;
    int nl;
    int i;

    list = data->cmd_lst;
    first = 0;
    nl = 0;
    while (list)
	{
		i = 0;
		while (list->c_args[i])
		{
            if (ft_strcmp("echo", list->c_args[i]) == 0 && first == 0)
            {
                first = i + 1;
                i++;
            }
            if (first)
            {
                if (!nl && ft_strcmp("-n", list->c_args[first]) == 0)
                {
                    i++;
                    nl = 1;
                }
                ft_putstr_fd(list->c_args[i], 1);
                if (list->c_args[i + 1])
                    ft_putstr_fd(" ", 1);
            }
            i++;
		}
		list = list->nx;
	}
    if (!nl)
        ft_putstr_fd("\n", 1);
}
