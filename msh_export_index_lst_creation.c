/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_index_lst_creation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:09:51 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/01 17:59:07 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  ****  THIS FUNCTION WILL BE CALLED BY A FEW WAYS: ****
 * 		A)  ft_index_lstadd_back(index, ft_index_new_nd(src));
 * 		B)	ft_index_lstadd_front(index, ft_index_new_nd(src));
 * 		C)	ft_index_lstadd_mid(prev, ft_index_new_nd(src));
 * 	where 'src' will be a pointer to the appropiate node of index_lst
 * 
 * @param nd            The new node to be added to index_lst
 * @return t_env_lst* 	A pointer to the new node
 */
t_env_lst	*ft_index_new_nd(t_env_lst *nd)
{
	t_env_lst	*new;

	new = (t_env_lst *)malloc(sizeof(t_env_lst));
	new->nm = ft_strdup(nd->nm);
	new->equal = nd->equal;
	new->val = ft_strdup(nd->val);
	new->nx = NULL;
	return (new);
}

/**
 * @brief 		*** IT WILL BE CALLED BY ft_export_print_lst ***
 * 			(which liberates the index_lst after the printing)
 *  Recorring env list element by element, finding its destiny position
 *  in the aux list: 
 *  - into the 'if'   -> goes in the 1st position;
 *  - into the 'else' -> into the 'if'   -> goes in the last position;
 *  -                 -> into the 'else' -> goes in an intermediate pos;
 * @return t_env_lst* 
 */
t_env_lst	*ft_index_built_lst(t_msh *data)
{
	t_env_lst	*idx;
	t_env_lst	*r_idx;
	t_env_lst	*src;

	src = data->env_lst;
	idx = NULL;
	idx = ft_index_lstadd_front(idx, ft_index_new_nd(src));
	while (src->nx != NULL)
	{
		r_idx = idx;
		if (ft_strcmp(src->nx->nm, r_idx->nm) < 0)
			idx = ft_index_lstadd_front(idx, ft_index_new_nd(src->nx));
		else
		{
			while (r_idx->nx != NULL
				&& ft_strcmp(src->nx->nm, r_idx->nx->nm) > 0)
				r_idx = r_idx->nx;
			if (r_idx->nx == NULL)
				ft_index_lstadd_back(r_idx, ft_index_new_nd(src->nx));
			else
				ft_index_lstadd_mid(r_idx, ft_index_new_nd(src->nx));
		}
		src = src->nx;
	}
	return (idx);
}
