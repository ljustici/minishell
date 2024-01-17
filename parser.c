/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:52:19 by ljustici          #+#    #+#             */
/*   Updated: 2024/01/17 18:52:03 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int contains_var(char *token)
{
	int i;
	size_t len;

	len = ft_strlen(token);
	i = 0;
	while(i < (int)len)
	{
		if (is_var(&token[i]))
			return(i);
		i++;
	}
	return(-1);
}

size_t get_end_of_var(char *token)
{
	size_t i;

	i = 0;
	span_var_in_dqt(token, &i, ft_strlen(token));
	return(i);
}

/**
 * Adds the characters found before or after a variable, if any.
*/
char *format_expansion_token(char *token, char *expanded, size_t end, int start)
{
	char *result;
	char *tail;

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
		//printf("result: %s end:%zu\n", result, end);
		free(tail);
	}
	free(expanded);
	expanded = NULL;
	return(result);
}

/**
 * If a token is delimited by simple quotes, these must be removed, but not
 * any double quote that might be inside.
 * If a token is delimited by double quotes, these must be removed, but not
 * any simple quote that might be inside.
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
	//printf("len: %d\n", len);
	parsed = (char **)ft_calloc(len + 1, sizeof(char *));
	while(i < len)
	{
       	if (has_qts(tokens[i], '\''))
            parsed[j] = clean_quotes(tokens[i], '\'');
		if (has_qts(tokens[i], '\"') > 1)
            parsed[j] = clean_quotes(tokens[i], '\"');
		else if (!has_qts(tokens[i], '\'') && has_qts(tokens[i], '\"') == 1)
            parsed[j] = clean_quotes(tokens[i], '\"');
		else
			parsed[j] = ft_strdup(tokens[i]);
		//if (parsed[j])
		//	printf("parsed: %s  i:%d\n", parsed[j], j);
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

void	free_rds_list(t_rd *list)
{
	t_rd	*next;

	while (list)
	{
		next = list->nx;
		free(list->file);
		free(list);
		list = next;
	}
}

void free_cmd_list(t_cmd *test)
{
	while(test)
	{
		ft_free_array(test->c_args);
		free_rds_list(test->rds);
		free(test);
		test = test->nx;
	}
}

void print_command_test(t_cmd *list)
{
	t_cmd *test;
	
	test = list;
	int i = 0;
	if (!list)
		printf("no hay lista\n");
	while(list)
	{
		i = 0;
		while(list->c_args[i])
		{
			printf("-- %i content: %s\n", i, list->c_args[i]);
			i++;
		}
		t_rd *print = list->rds;
		while(print)
		{
			printf("----- Nodo redir\n");
			printf("-- redir: file %s\n",print->file);
			printf("-- redir: endkey %s\n",print->endkey);
			print = print->nx;
		}
		list = list->nx;
	}
}

void ft_parse(char **tokens, t_msh *data)
{
	char **expanded;
	char **parsed;
	int len;
	t_cmd *list;
	
	list = NULL;
	//printf("ft_parse\n");
	expanded = expanding_loop(tokens, data->env_lst);
	int i=0;
	while(expanded[i])
    {
        //printf("expanded: %s\n", expanded[i]);
        i++;
    }
	parsed = parse_token_array(expanded);
	i = 0;
	while(parsed[i])
    {
        //printf("after parsed: %s\n", parsed[i]);
        i++;
    }
	len = ft_array_len(parsed);
	if (len == 0)
	{
		ft_free_array(parsed);
		return ;
	}
	if (check_token_syntax(parsed, data))
		return ;
	
	create_list(&data->cmd_lst, parsed, len);
	ft_free_array(parsed);
	//data->cmd_lst = list;
	//print_command_test(list);
	//free_cmd_list(list);
}
