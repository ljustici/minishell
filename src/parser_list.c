/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:29:49 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/21 20:38:31 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void add_redir_to_node(t_cmd *node, char *filename)
{
	node->rds = (t_rd*)malloc(sizeof(t_rd));
	node->rds->file = ft_strdup(filename);
}

t_cmd	*create_node(char **tokens, int end)
{
	t_cmd	*node;
	int			i;

	i = 0;
	node = (t_cmd *)malloc(sizeof(t_cmd));
	node->c_args = (char **)ft_calloc(end + 1, sizeof(char *));
	if (!node)
		return (0);
	node->type = set_token_type(tokens[0]);
    while(i < end)
	{
		node->c_args[i] = ft_strdup(tokens[i]);
		printf("nodo: %s  i: %i\n", node->c_args[i], i);
		i++;
	}
	node->c_args[i] = 0;
	node->next = 0;
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
		while (go_to_last->next)
			go_to_last = go_to_last->next;
		go_to_last->next = node;
	}
	node->next = 0;
}

/**
 * A token segment is composed by the first word and its flags and/or arguments
 * Token segments are separated by pipes. 
 * Redirections must not be included in the arguments of a token.
*/
int get_end_of_segment(char **tokens)
{
	int i;

	i = 0;
	while(tokens[i] && tokens[i + 1])
	{
		if (is_pipe(tokens[i + 1]) || is_redir(tokens[i + 1]))
		{
			i++;
			return(i);
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
	int	i;
	int end;
	t_cmd *node;

	i = 0;
	end = 1;
	while (i < n)
	{	
		if (is_pipe(tokens[i]) && n > 1)
			i++;
		if (is_redir(tokens[i]))
		{
			add_redir_to_node(node, tokens[i + 1]);
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
	ft_free_array(tokens);
}

