/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_index_lstadd_node.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:09:39 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/01 17:59:36 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * @param index 	    A pointer to the first node of the index_lst
 * @param nd 	        A pointer to the new node to be added
 *  
 */
void	*ft_index_lstadd_back(t_env_lst *index, t_env_lst *nd)
{
	if (index == NULL && nd)
	{
		index = nd;
		return (index);
	}
	while (index->nx != NULL)
		index = index->nx;
	index->nx = nd;
	return (index);
}

/**
 * @brief 
 * 
 * @param index  	    A pointer to the first node of index_lst
 * @param nd  	        A pointer to the new node to be added
 * @return t_env_lst* 	A pointer to the new first node of index_lst
 */
t_env_lst	*ft_index_lstadd_front(t_env_lst *index, t_env_lst *nd)
{
	t_env_lst	*new_head;

	if (index == NULL)
	{
		new_head = nd;
		new_head->nx = NULL;
		return (new_head);
	}
	new_head = nd;
	new_head->nx = index;
	return (new_head);
}

/**
 * @brief 
 * 
 * @param prev 	   A pointer to the previous node of index_lst
 * 				(which '->nx' will be point to the new node)
 * @param nd 	   The new node to be added after the prev node
 * 		(which '->nx' will be point to the origin node pointed by prev)
 * 
 */
void	ft_index_lstadd_mid(t_env_lst *prev, t_env_lst *nd)
{
	nd->nx = prev->nx;
	prev->nx = nd;
}
