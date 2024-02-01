/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:58:13 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/01 20:43:20 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_all_n(char *s)
{
    size_t i;
    size_t len;

    len = ft_strlen(s);
    i = 0;
    if (s[0] != '-')
        return (0);
    i++;
    while(i < len)
    {
        if (s[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

/*void    echo_args(char **c_args, int i, int *nl,)
{
    if (first)
    {
        if (!nl && c_args[first] && is_all_n(c_args[first]))
        {
            i++;
            nl = 1;
        }
        if (c_args[i])
            ft_putstr_fd(c_args[i], 1);
        if (c_args[i + 1])
            ft_putstr_fd(" ", 1);
    }
}*/

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
            if ((ft_strcmp("echo", list->c_args[i]) == 0 || ft_strcmp("ECHO", list->c_args[i]) == 0) && first == 0)
            {
                first = i + 1;
                i++;
                if (first)
                {
                    if (!nl && list->c_args[first] && is_all_n(list->c_args[first]))
                    {
                        i++;
                        nl = 1;
                    }
                    else
                        printf("c: %s\n", list->c_args[first]);
                    if (list->c_args[i])
                        ft_putstr_fd(list->c_args[i], 1);
                    else
                        break;
                    if (list->c_args[i + 1])
                        ft_putstr_fd(" ", 1);
                }
            }
            i++;
		}
		list = list->nx;
	}
    if (!nl)
        ft_putstr_fd("\n", 1);
}
