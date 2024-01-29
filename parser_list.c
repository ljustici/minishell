/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:29:49 by ljustici          #+#    #+#             */
/*   Updated: 2024/01/28 16:20:37 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_node(char **tokens, int end)
{
	t_cmd	*node;
	int		i;

	i = 0;
	node = (t_cmd *)malloc(sizeof(t_cmd));
	node->c_args = (char **)ft_calloc(end + 1, sizeof(char *));
	if (!node)
		return (0);
	while (i < end && !is_redir(tokens[i]))
	{
		node->c_args[i] = ft_strdup(tokens[i]);
		i++;
	}
	node->c_args[i] = 0;
	node->c_env_path = 0;
	node->rds = 0;
	node->nx = 0;
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

void	node_add_back_rd(t_rd **head, t_rd *node)
{
	t_rd	*go_to_last;

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

void	add_redir_to_node(t_rd **list, char *info, char *token)
{
	t_rd	*node;
	t_rd	**span;

	span = list;
	node = (t_rd *)malloc(sizeof(t_rd));
	node->type = set_redir_type(token);
	if (node->type == 1 || node->type == 3 || node->type == 4)
	{
		node->file = ft_strdup(info);
		node->endkey = NULL;
	}
	else if (node->type == 2)
	{
		node->endkey = ft_strdup(info);
		node->file = NULL;
	}
	node->heredoc = NULL;
	node->nx = 0;
	node_add_back_rd(span, node);
}

/**
 * A token segment is composed by the first word and its flags and/or arguments
 * Token segments are separated by pipes. 
 * Redirections must not be included in the arguments of a token, unless they are
 * the last argument or the only argument.
*/
int	get_end_of_segment(char **tokens)
{
	int	i;
	int	n;

	n = ft_array_len(tokens) - 1;
	i = 0;
	while (tokens[i] && tokens[i + 1])
	{
		if ((is_pipe(tokens[i + 1]) || is_redir(tokens[i + 1])))
		{
			i++;
			return (i);
		}
		i++;
	}
	i++;
	return (i);
}

/**
 * Creates a list of nodes by separating the token array into segments
 * and creating a new node with each of these segments, then adding 
 * one after another.
 * Segments are delimited by pipes or null.
 * Pipes must not be either the start of a node or included in its
 * arguments.
 * If there is a redirection, it will be added to the previous node along
 * with the next token, which must be the filename. The loop will
 * restart after this filename.
*/
void	create_list(t_cmd **list, char **tokens, int n)
{
	int		i;
	int		end;
	t_cmd	*node;

	i = 0;
	end = 1;
	node = NULL;
	printf("Create list\n");
	while (i < n)
	{
		if (is_pipe(tokens[i]) && n > 1 && i != 0 && i < n - 1)
			i++;
		if (is_redir(tokens[i]) && i < n - 1)
		{
			if (!node)
			{
				node = create_node(&tokens[i], end);
				node_add_back(list, node);
			}
			add_redir_to_node(&(node->rds), tokens[i + 1], tokens[i]);
			i = i + 2;
		}
		else
		{
			end = get_end_of_segment(&tokens[i]);
			node = create_node(&tokens[i], end);
			node_add_back(list, node);
			i = i + end;
		}
	}
}
