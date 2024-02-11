/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:50:20 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/11 14:56:00 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_add_back_rd(t_cmd **head, t_rd *node)
{
	t_rd	*go_to_last;

	go_to_last = (*head)->rds;
	if (!node)
		return ;
	if (!(*head)->rds)
		(*head)->rds = node;
	else
	{
		go_to_last = (*head)->rds;
		while (go_to_last->nx)
			go_to_last = go_to_last->nx;
		go_to_last->nx = node;
	}
}

void	add_redir_to_node(t_cmd **cmd, char *info, char *token)
{
	t_rd	*list;

	list = (t_rd *)malloc(sizeof(t_rd));
	if (!list)
		(*cmd)->orgn->error = ERROR_MALLOC_ERROR;
	list->type = set_redir_type(token);
	if (list->type == 1 || list->type == 3 || list->type == 4)
	{
		list->file = ft_strdup(info);
		list->endkey = NULL;
	}
	else if (list->type == 2)
	{
		list->endkey = ft_strdup(info);
		list->file = NULL;
	}
	list->heredoc = NULL;
	list->nx = 0;
	node_add_back_rd(cmd, list);
}

/*void	free_rds_list(t_rd *list)
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
}*/
