/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_naming.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:30:06 by ljustici          #+#    #+#             */
/*   Updated: 2024/01/28 15:55:59 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * A token is a word (command or arg) if its characters are:
 * - not any other type of token
 * - printable characters
*/
int	is_word(char *token)
{
	size_t	i;

	i = 0;
	while (token[i])
	{
		if (!ft_isprint(token[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * A token is a flag if it starts with - and its next character is
 * alphabetic
*/
int	is_flag(char *token)
{
	if (token[0] == '-' && ft_isalpha(token[1]))
		return (2);
	return (0);
}

/**
 * A token is a redirection if:
 * - it starts with > and ends or follows with another >
 * - it starts with < and ends or follows with another <
*/
int	is_redir(char *token)
{
	if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
		return (1);
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
		return (1);
	return (0);
}

/**
 * A token is a pipe if it starts with | and ends.
*/
int	is_pipe(char *token)
{
	if (token[0] == '|' && !token[1])
		return (1);
	return (0);
}

/**
 * Returns the type of redirection
*/
int	set_redir_type(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (1);
	else if (ft_strcmp(token, "<<") == 0)
		return (2);
	else if (ft_strcmp(token, ">") == 0)
		return (3);
	else if (ft_strcmp(token, ">>") == 0)
		return (4);
	return (0);
}
