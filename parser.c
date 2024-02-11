/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:52:19 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/11 13:01:19 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_var(char *token)
{
	int		i;
	size_t	len;

	len = ft_strlen(token);
	i = 0;
	while (i < (int)len)
	{
		if (is_var(&token[i]))
			return (i);
		i++;
	}
	return (-1);
}

size_t	get_end_of_var(char *token)
{
	size_t	i;

	i = 0;
	span_var_in_dqt(token, &i, ft_strlen(token));
	return (i);
}

/**
 * Adds the characters found before or after a variable, if any.
*/
char	*format_expansion_token(char *token, char *expanded, size_t end,
		int start)
{
	char	*result;
	char	*tail;

	result = NULL;
	if (start == 0 && expanded)
		result = ft_strdup(expanded);
	else if (start > 0 && expanded)
		result = ft_join_free(ft_substr(token, 0, start), expanded);
	else
		result = ft_substr(token, 0, start);
	if (end < ft_strlen(token))
	{
		tail = ft_substr(token, end, ft_strlen(token));
		result = ft_join_free(result, tail);
		free(tail);
	}
	return (result);
}

/**
 * If a token is delimited by simple quotes, these must be removed, but not
 * any double quote that might be inside.
 * If a token is delimited by double quotes, these must be removed, but not
 * any simple quote that might be inside.
 * The loop must then span to the next token so that literal quotes inside
 * the tokens don't get removed.
*/
char	**parse_token_array(char **tokens)
{
	int		i;
	int		j;
	int		len;
	char	**parsed;

	i = 0;
	j = 0;
	len = ft_array_len(tokens);
	parsed = (char **)ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		if (should_clean_quotes(tokens[i], &parsed[j]) == 1)
			quote_section_cleaner(tokens[i], &parsed[j], ft_strlen(tokens[i]));
		i++;
		j++;
	}
	parsed[j] = 0;
	return (parsed);
}

void	ft_parse(char **tokens, t_msh *data)
{
	char	**expanded;
	char	**parsed;
	int		len;

	data->cmd_lst = NULL;
	expanded = expanding_loop(tokens, data);
	if (check_token_syntax(expanded, data))
	{
		ft_free_array(expanded);
		return ;
	}
	parsed = parse_token_array(expanded);
	ft_free_array(expanded);
	len = ft_array_len(parsed);
	if (len == 0)
	{
		ft_free_array(parsed);
		return ;
	}
	data->cmd_lst = NULL;
	create_list(&data->cmd_lst, parsed);
	ft_free_array(parsed);
}

/*void	print_command_test(t_cmd *list)
{
	t_cmd	*test;
	int		i;
	t_rd	*print;

	test = list;
	i = 0;
	if (!list)
		printf("no hay lista\n");
	while (list)
	{
		i = 0;
		printf("----- Empieza un nodo ------\n");
		while (list->c_args[i])
		{
			printf("-- %i content: %s\n", i, list->c_args[i]);
			i++;
		}
		print = list->rds;
		if (!print)
			printf("----- no hay lista de redireccionamientos\n");
		while (print)
		{
			printf("----- redir del nodo\n");
			printf("-- redir: file %s]\n", print->file);
			printf("-- redir: endkey %s\n", print->endkey);
			print = print->nx;
		}
		list = list->nx;
	}
}*/
