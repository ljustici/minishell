/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:52:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/15 21:27:22 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * If a token is delimited by simple quotes, these must be removed, but not
 * any double quote that might be inside.
 * If a token is delimited by double quotes, these must be removed, but not
 * any simple quote that might be inside.
 * If a token has a hanging double quote it must be removed because double
 * quotes become more than one token.
 * The loop must then span to the next token so that literal quotes inside
 * the tokens don't get removed.
*/
char **parse_token_array(char **tokens)
{
	int i;
	int len;
	char **parsed;
	
	i = 0;
	len = ft_array_len(tokens);
	parsed = (char **)ft_calloc(len + 1, sizeof(char *));
	while(i < len)
	{
		if (set_token_type(tokens[i]) == 0)
			return(NULL); //error
        if (has_qts(tokens[i], '\'') == 2)
            parsed[i] = clean_quotes(tokens[i], '\'');
		else if (has_qts(tokens[i], '\"') == 2)
            parsed[i] = clean_quotes(tokens[i], '\"');
		else if (has_qts(tokens[i], '\"') == 1)
            parsed[i] = clean_quotes(tokens[i], '\"');
		else
			parsed[i] = tokens[i];
		i++;
	}
	parsed[i] = 0;
	ft_free_array(tokens);
	return(parsed);
}

int	ft_array_len(char **str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
