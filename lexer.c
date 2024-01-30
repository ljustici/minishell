/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:11:36 by ljustici          #+#    #+#             */
/*   Updated: 2024/01/30 18:30:58 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open_quote(char *line, char *first, int *i)
{
	int	is_opening;

	is_opening = 0;
	if (*i == -1 || line[*i])
		(*i)++;
	else
		return (is_opening);
	while (line[*i] && (*i < (int)ft_strlen(line)))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			is_opening = 1;
			*first = line[*i];
			break ;
		}
		(*i)++;
	}
	return (is_opening);
}

int	check_closing_quote(char *line, char *first, int *i)
{
	int	is_closing;

	is_closing = 0;
	if (!line[*i])
		return (is_closing);
	while (line[(*i)++] && (*i < (int)ft_strlen(line)))
	{
		if (line[*i] == *first)
		{
			is_closing = 1;
			break ;
		}
	}
	return (is_closing);
}

int	check_quotes(char *line)
{
	char	first;
	int		pair;
	int		i;

	i = -1;
	first = '\0';
	pair = 0;
	while ((i == -1 || line[i]) && (i < (int)ft_strlen(line)))
	{
		pair = check_open_quote(line, &first, &i);
		if (pair == 1 || pair % 2 != 0)
			pair = pair + check_closing_quote(line, &first, &i);
		first = '\0';
	}
	if (pair % 2 == 0)
		return (0);
	return (1);
}

char	**split_line(char *line, t_msh *data)
{
	char	**tokens;

	tokens = NULL;
	if (check_quotes(line) != 0)
	{
		error_syntax_token(data, "", ERROR_QUOTE);
		return (NULL);
	}
	tokens = split_by_metachar(line, data);
	return (tokens);
}

int	ft_lexer(t_msh *data)
{
	char	**result;
	int		i;

	if (is_all_spaces(data->pipeline)) //debe ser guardado en el historial
		return (1);
	result = split_line(data->pipeline, data);
	if (!result)
		return (1);
	i = 0;
	while (i < ft_array_len(result))
	{
		//printf("token: %s\n", result[i]);
		i++;
	}
	ft_parse(result, data);
	return (0);
}
