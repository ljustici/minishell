/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:52:19 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/21 21:03:45 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Variables need to be replaced by their content, unless they are literals that
 * look like variables:
 * - variables inside simple quotes
 * - dollars followed by a quote then by characters
 * They must be checked before cleaning quotes from tokens.
*/
//char *var_expansion(char *token)
//{
	
//}

/**
 * If a token is delimited by simple quotes, these must be removed, but not
 * any double quote that might be inside.
 * If a token is delimited by double quotes, these must be removed, but not
 * any simple quote that might be inside.
 * If a token has a hanging double quote it must be removed because double
 * quotes become more than one token. However, in tokens enclosed by simple
 * quotes (like 'm"o') it must not be removed.
 * The loop must then span to the next token so that literal quotes inside
 * the tokens don't get removed.
*/
char **parse_token_array(char **tokens)
{
	int i;
	int j;
	int len;
	char **parsed;
	
	i = 0;
	j = 0;
	len = ft_array_len(tokens);
	parsed = (char **)ft_calloc(len + 1, sizeof(char *));
	while(i < len)
	{
		//if (is_var(tokens[i]))
		//	parsed[i] = var_expansion(tokens[i]);
        //else 
		if (has_qts(tokens[i], '\'') == 2)
            parsed[j] = clean_quotes(tokens[i], '\'');
		else if (has_qts(tokens[i], '\"') == 2)
            parsed[j] = clean_quotes(tokens[i], '\"');
		else if (!has_qts(tokens[i], '\'') && has_qts(tokens[i], '\"') == 1)
            parsed[j] = clean_quotes(tokens[i], '\"');
		else
			parsed[j] = ft_strdup(tokens[i]);
		printf("parsed: %s  i:%d\n", parsed[j], j);
		i++;
		if (parsed[j])
			j++;
		else
			free(parsed[j]);
		
	}
	parsed[j] = 0;
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

void	free_list(t_rd *list)
{
	t_rd	*next;

	while (list)
	{
		next = list->next;
		free(list->file);
		free(list);
		list = next;
	}
}

void ft_parse(char **tokens)
{
	char **parsed;
	int len;
	t_cmd *list;
	t_cmd *test;

	list = NULL;
	parsed = parse_token_array(tokens);
	len = ft_array_len(parsed);
	create_list(&list, parsed, len);
	test = list;
	int i = 0;
	while(list)
	{
		printf("- type: %i\n", list->type);
		i = 0;
		while(list->c_args[i])
		{
			printf("-- content: %s\n", list->c_args[i]);
			printf("-- redir: %s\n",list->rds[i].file);
			i++;
		}
		list = list->next;
	}
	while(test)
	{
		ft_free_array(test->c_args);
		if (test->rds)
			free_list(test->rds);
		free(test);
		test = test->next;
	}
}
