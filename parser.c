/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:52:19 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/10 15:39:06 by ljustici         ###   ########.fr       */
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
		//printf("Dentro de parse token array\n");
		if (should_clean_quotes(tokens[i], &parsed[j]) == 1)
			quote_section_cleaner(tokens[i], &parsed[j], ft_strlen(tokens[i]));
		//printf("parse token array: [%s]\n",parsed[j]);
		i++;
		j++;
	}
	parsed[j] = 0;
	return (parsed);
}

/*void swap_tokens(char **a, char **b)
{
	char *temp;

	temp = ft_strdup(*a);
	free(*a);
	*a = ft_strdup(*b);
	free(*b);
	b = ft_strdup(temp);
}*/
/*
int should_rotate(char **tokens, int len)
{
	int i;

	i = 0;
	if (is_redir(tokens[0]) && tokens[2])
		return (1);
	return (0);
	
	
}

char **do_redir_rotate(char **tokens, int len)
{
	char **new_arr;
	int i;

	i = 0;
	new_arr = (char **)malloc(sizeof(char *) * (len + 1));
	while(i < len)
	{
		if (i == len - 2)
			new_arr[i] = ft_strdup(tokens[0]);
		else if (i == len - 1)
			new_arr[i] = ft_strdup(tokens[1]);
		else
			new_arr[i] = ft_strdup(tokens[i + 2]);
		i++;
	}
	new_arr[len] = 0;
	i = 0;
	while(i < len)
	{
		printf("Reordered tokens: %s\n", new_arr[i]);
		i++;
	}
	ft_free_array(tokens);
	return(new_arr);
}*/

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

void	free_cmd_list(t_cmd *test)
{
	while (test)
	{
		ft_free_array(test->c_args);
		free_rds_list(test->rds);
		free(test);
		test = test->nx;
	}
}

void	print_command_test(t_cmd *list)
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
	//print_command_test(data->cmd_lst);
	ft_free_array(parsed);
}
