/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:58:13 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/18 18:00:49 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_if_echo(t_cmd *list, int *i, int *first)
{
	if ((ft_strcmp("echo", list->c_args[0]) == 0 || ft_strcmp("ECHO",
				list->c_args[0]) == 0) && *first == 0)
	{
		*first = *i + 1;
		(*i)++;
	}
}

static int	fill_echo(t_msh *data, t_cmd *list, int *i)
{
	if (list->c_args[*i])
	{
		if (data->echo == NULL)
			data->echo = ft_strdup(list->c_args[*i]);
		else
			data->echo = ft_strjoin_free(data->echo, list->c_args[*i]);
	}
	else
		return (1);
	if (list->c_args[*i + 1])
		data->echo = ft_strjoin_free(data->echo, " ");
	return (0);
}

static void	print_echo(t_msh *data, int nl)
{
	if (!nl)
		data->echo = ft_strjoin_free(data->echo, "\n");
	ft_putstr_fd(data->echo, 1);
}

static void	clean_echo(t_msh *data)
{
	free(data->echo);
	data->echo = NULL;
	data->exit_code = 0;
}

void	ft_builtin_echo(t_msh *data, t_cmd *list)
{
	int	first;
	int	nl;
	int	i;

	nl = 0;
	i = 0;
	first = 0;
	while (list->c_args[i])
	{
		set_if_echo(list, &i, &first);
		if (first)
		{
			if (!nl && list->c_args[first] && is_all_n(list->c_args[first]))
			{
				while (is_all_n(list->c_args[i]))
					i++;
				nl = 1;
			}
			if (fill_echo(data, list, &i) == 1)
				break;
		}
		i++;
	}
	print_echo(data, nl);
	clean_echo(data);
}
