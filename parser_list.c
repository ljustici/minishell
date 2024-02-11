/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:29:49 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/11 13:53:38 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Fills an array with its corresponding command and its parameters
*/
char	**fill_command_array(char **tokens, int *j, int end)
{
	int		i;
	char	**args;

	args = (char **)ft_calloc((end + 1), sizeof(char *));
	if (!args)
		return (0);
	i = 0;
	while (i < end)
	{
		if (!is_redir(tokens[i]))
		{
			args[*j] = ft_strdup(tokens[i]);
			(*j)++;
			i++;
		}
		else
			i = i + 2;
	}
	return (args);
}

/**
 * Adds null to the values of the node
*/
void	finalize_node(t_cmd **node, int j)
{
	(*node)->c_args[j] = 0;
	(*node)->c_env_path = 0;
	(*node)->nx = 0;
	(*node)->rds = 0;
}

/**
 * Creates a node for each command, including all its redirections
*/
t_cmd	*create_node(char **tokens, int end)
{
	t_cmd	*node;
	int		i;
	int		j;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->c_args = NULL;
	j = 0;
	node->c_args = fill_command_array(tokens, &j, end);
	finalize_node(&node, j);
	i = 0;
	while (i < end)
	{
		if (is_redir(tokens[i]))
		{
			add_redir_to_node(&node, tokens[i + 1], tokens[i]);
			i = i + 2;
		}
		else
			i++;
	}
	return (node);
}

void	node_add_back(t_cmd **head, t_cmd *node)
{
	t_cmd	*go_to_last;

	if (!*head)
		*head = node;
	else
	{
		go_to_last = *head;
		while (go_to_last->nx)
			go_to_last = go_to_last->nx;
		go_to_last->nx = node;
	}
}

void	create_list(t_msh *data, t_cmd **list, char **tokens)
{
	int		i;
	t_cmd	*node;
	int		n;
	int		j;

	node = NULL;
	i = 0;
	j = 0;
	n = ft_array_len(tokens);
	while (i < n)
	{
		while (j < n && !is_pipe(tokens[j]))
			j++;
		node = create_node(&tokens[i], j - i);
		if (!node)
			data->error = ERROR_MALLOC_ERROR;
		node_add_back(list, node);
		i = j;
		i++;
		j++;
	}
}
