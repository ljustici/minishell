/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:35:48 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/11 12:28:47 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_spnltab(char c)
{
	if (!c)
		return (1);
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_metacharacter(char c)
{
	if (!c)
		return (0);
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	should_split(char c)
{
	if (is_spnltab(c) == 1 || is_metacharacter(c) == 1)
		return (1);
	return (0);
}

void	span_until_quote(const char *s, unsigned long *i, char quote)
{
	*i = *i + 1;
	while ((*i) < ft_strlen(s) && s[*i] != quote)
		*i = *i + 1;
}

int	is_all_spaces(char *input)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(input);
	while (i < n)
	{
		if (input[i] != ' ')
			break ;
		i++;
	}
	if (i == n)
		return (1);
	return (0);
}
