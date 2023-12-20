/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export_index_lst_creation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:09:51 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/10/29 16:09:52 by roruiz-v         ###   ########.fr       */
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
 * @return t_env_lst* 
 */
t_env_lst	*ft_index_built_lst(t_msh *data)
{
	t_env_lst	*idx;	// puntero a la cabeza de index
	t_env_lst	*r_idx; // puntero que recorre index en cada bucle interior
	t_env_lst	*src;	// puntero que recorre env_lst en cada bucle exterior

	src = data->env_lst;
	idx = NULL;
	idx = ft_index_lstadd_front(idx, ft_index_new_nd(src)); // es creada con primer nodo
	while (src->nx != NULL) // recorremos env_lst elemento a elemento
	{
		r_idx = idx;		// reiniciamos index para cada elemento de env_lst
		if (ft_strcmp(src->nx->nm, r_idx->nm) < 0) // encontramos que va el prime
			idx = ft_index_lstadd_front(idx, ft_index_new_nd(src->nx));
		else				// avanzamos hasta encontrar un nm <=
		{
			while (r_idx->nx != NULL && ft_strcmp(src->nx->nm, r_idx->nx->nm) > 0)
				r_idx = r_idx->nx;
			if (r_idx->nx == NULL) // estamos al final de index, lo agregamos como último
				ft_index_lstadd_back(r_idx, ft_index_new_nd(src->nx));
			else // punto de inserción directa
				ft_index_lstadd_mid(r_idx, ft_index_new_nd(src->nx));
		}
		src = src->nx;		// siguiente nodo de env_lst a tratar
	}
	return (idx);
}
