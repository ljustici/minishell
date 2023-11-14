/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_simple_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:39:02 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/14 18:41:05 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_simple_parser(t_msh *data)
{
	if (data->error != NO_ERROR)
		return ;
	data->fd = 1;	
}

int	ft_env_forbidden_chars(char *name)
{
	int	i;

	i = 0;	
	if (!((name[i] >= 'A' && name[i] <= 'Z')
		|| (name[i] >= 'a' && name[i] <= 'z')
		|| (name[i] == '_')))
		return (1);
	while (name[++i])
	{
		if (!((name[i] >= 'A' && name[i] <= 'Z')
			|| (name[i] >= 'a' && name[i] <= 'z')
			|| (name[i] >= '0' && name[i] <= '9')
			|| (name[i] == '_')))
			return (1);
	}
	return (0);
}

