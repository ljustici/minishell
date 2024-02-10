/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:58:13 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/10 18:05:19 by ljustici         ###   ########.fr       */
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

void	ft_builtin_echo(t_msh *data, t_cmd *list)
{
    int first;
    int nl;
    int i;

    nl = 0;
    i = 0;
    first = 0;
    while (list->c_args[i])
    {
        if ((ft_strcmp("echo", list->c_args[0]) == 0 || ft_strcmp("ECHO", list->c_args[0]) == 0) && first == 0)
        {
            first = i + 1;
            i++;
        }
        if (first)
        {
            if (!nl && list->c_args[first] && is_all_n(list->c_args[first]))
            {
                while (is_all_n(list->c_args[i]))
                    i++;
                nl = 1;
            }
            if (list->c_args[i])
            {
                if (data->echo == NULL)
                    data->echo = ft_strdup(list->c_args[i]);
                else
                    data->echo = ft_strjoin_free(data->echo, list->c_args[i]);
            }
            else
                break;
            if (list->c_args[i + 1])
                data->echo = ft_strjoin_free(data->echo, " ");
        }
        i++;
    }
    if (!nl)
        data->echo = ft_strjoin_free(data->echo, "\n");
    ft_putstr_fd(data->echo, 1);
    free(data->echo);
    data->echo = NULL;
}
