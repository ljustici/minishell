/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:17:57 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/11 13:10:00 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Returns true if there are two consecutive redirections
*/
int	is_double_redir(char **args, char **wrong_tk)
{
	int	i;
	int	n;

	i = 0;
	n = ft_array_len(args);
	while (i < n && n > 1)
	{
		if (is_redir(args[i]))
		{
			if (args[i + 1] && is_redir(args[i + 1]))
			{
				*wrong_tk = args[i + 1];
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	is_double_pipe(char **args, char **wrong_tk)
{
	int	i;
	int	n;

	i = 0;
	n = ft_array_len(args);
	while (i < n)
	{
		if (ft_strcmp(args[i], "||") == 0)
		{
			*wrong_tk = args[i];
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (ft_strcmp(args[i], "|") == 0 && ft_strcmp(args[i + 1], "|") == 0)
		{
			*wrong_tk = args[i];
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * Returns true if there is any orphan redirection:
 * - the last argument is a redirection
 * - the only argument is a redirection
*/
int	is_orphan_redir(char **args)
{
	int	n;

	n = ft_array_len(args);
	if (is_redir(args[n - 1]))
		return (1);
	return (0);
}

int	is_redir_pipe(char **args)
{
	int	i;
	int	n;

	i = 0;
	n = ft_array_len(args);
	while (i < n)
	{
		if (ft_strcmp(args[i], "<<") == 0 && ft_strcmp(args[i + 1], "|") == 0)
			return (1);
		else if (ft_strcmp(args[i], ">>") == 0
			&& ft_strcmp(args[i + 1], "|") == 0)
			return (1);
		else if (ft_strcmp(args[i], "<") == 0 && ft_strcmp
			(args[i + 1], "|") == 0)
			return (1);
		else if (ft_strcmp(args[i], ">") == 0
			&& ft_strcmp(args[i + 1], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * |
 * <
 * ||||
 * <<<<<
 * |a
 * a|
 * TODO: cmd | | cmd
*/
int	check_token_syntax(char **tokens, t_msh *data)
{
	int		n;
	int		is_wrong;
	char	*wrong_tk;

	wrong_tk = NULL;
	is_wrong = 1;
	n = ft_array_len(tokens);
	if (!n)
		return (0);
	if (ft_strcmp(tokens[0], "|") == 0 || ft_strcmp(tokens[n - 1], "|") == 0)
		error_syntax_token(data, tokens[0], ERROR_SYNTAX_UNEXPECTED_TOKEN);
	else if (is_double_redir(tokens, &wrong_tk))
		error_syntax_token(data, wrong_tk, ERROR_SYNTAX_UNEXPECTED_TOKEN);
	else if (is_orphan_redir(tokens))
		error_syntax_token(data, tokens[n - 1], ERROR_SYNTAX_UNEXPECTED_TOKEN);
	else if (is_redir_pipe(tokens))
		error_syntax_token(data, "|", ERROR_SYNTAX_UNEXPECTED_TOKEN);
	else if (is_double_pipe(tokens, &wrong_tk))
		error_syntax_token(data, wrong_tk, ERROR_SYNTAX_UNEXPECTED_TOKEN);
	else
	{
		is_wrong = 0;
	}
	return (is_wrong);
}
