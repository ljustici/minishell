/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_mfy_nds.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:10:02 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/01 17:17:49 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_env_mfy_or_add_nd(t_msh *data, t_env_lst *new);
void		ft_env_exchange_val(t_env_lst *t_nd, t_env_lst *new);
void		ft_env_join_val(t_env_lst *t_nd, t_env_lst *new);

/*  ************************************************************** */

void	ft_env_modify_or_add_node(t_msh *data, t_env_lst *new)
{
	if (!new)
		return ;
	if (data->env_lst == NULL)
		data->env_lst = new;
	else
		ft_env_mfy_or_add_nd(data, new);
}

/**
 * @brief      ******   BEWARE OF THIS  !!!!!   ******
 * 		When it's need to join, we first need to detect the correct '$NAME'
 * 
 * @param new 
 */
static void	ft_env_mfy_or_add_nd(t_msh *data, t_env_lst *new)
{
	t_env_lst	*t;

	t = data->env_lst;
	if (ft_str_equal(t->nm, new->nm))
		ft_env_exchange_val(t, new);
	else
	{
		while (t->nx != NULL && !ft_str_equal(t->nx->nm, new->nm))
			t = t->nx;
		if (t->nx == NULL)
			t->nx = new;
		else
			ft_env_exchange_val(t->nx, new);
	}
}

void	ft_env_exchange_val(t_env_lst *t_nd, t_env_lst *new)
{
	ft_free_null_void_return(&t_nd->val);
	t_nd->val = ft_strdup(new->val);
	if (t_nd->equal == 0)
		t_nd->equal = new->equal;
	ft_free_envlst_node(new);
}

void	ft_env_join_val(t_env_lst *t_nd, t_env_lst *new)
{
	t_nd->val = ft_join_free(t_nd->val, new->val);
	if (t_nd->equal == 0)
		t_nd->equal = new->equal;
	ft_free_envlst_node(new);
}
