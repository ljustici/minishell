/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_echo_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 15:08:48 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/11 15:09:47 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_n(char *s)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	if (s[0] != '-')
		return (0);
	i++;
	while (i < len)
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
