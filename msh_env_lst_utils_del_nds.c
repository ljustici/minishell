/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_del_nds.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:35:44 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/01 17:07:51 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_envlst_node(t_env_lst *del_node)
{
	ft_free_null_void_return(&del_node->nm);
	ft_free_null_void_return(&del_node->val);
	free(del_node);
	del_node = NULL;
}

/**
 * @brief ** Allows to test if it's a valid env_var name before deleting **
 * 	           (If it contains forbidden chars, it's invalid)
 * 
 * @param del_nd   It will be liberated outside
 * @return int     1 -> forbidden char found; 0 -> not founded forbiddens
 */
static int	ft_env_forbidden_name(char *del_nd)
{
	if (del_nd && ft_detect_forbidden_chars(del_nd))
	{
		ft_putstr("msh: unset: ", 2);
		ft_putstr(del_nd, 2);
		ft_putstr(": not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

/**
 * @brief  *** DELETES THE NODE WHOSE NAME IS EQUIVALENT TO STRING ARGMT  ***
 * 
 *          *** 	IT WILL BE CALLED BY COMMAND "unset"   ***
 *   prints an error msg if contains forbbiden characters (nbrs, alpha...)
 *          --> MUST DO NOTHING IF NAME DOESN'T EXIST
 *  BEWARE OF THIS -> the string del_nd came from data->cmd_lst->c_args[1],
 *                    & it'll be freeded whenever the whole node.
 * 
 *  Inside the 'if' there's a 2nd 'if' that detects it there's none
 *   equivalence at all.
 *  Inside the 'else' we manage the 1st node coincidence, deleting the node.
 *  Any other case, outside the if/else, we manage an intermediate node
 *   coincidente, building a bridge & deleting the node.
 * 
 * @param del_nd   The ->nm string to find in the list
 */
void	ft_env_lstdelone(t_msh *data, char *del_nd)
{
	t_env_lst	*t;
	t_env_lst	*del;

	if (!data->env_lst || !del_nd || ft_env_forbidden_name(del_nd))
		return ;
	t = data->env_lst;
	if (!ft_str_equal(t->nm, del_nd))
	{
		while (t->nx != NULL && !ft_str_equal(t->nx->nm, del_nd))
			t = t->nx;
		if (t->nx == NULL)
			return ;
	}
	else
	{
		data->env_lst = t->nx;
		ft_free_envlst_node(t);
		return ;
	}
	del = t->nx;
	t->nx = t->nx->nx;
	ft_free_envlst_node(del);
}

/**
 * @brief   *** DELETES THE COMPLETE ENV VAR LIST ***
 */
void	ft_env_lstclear(t_env_lst *del_lst)
{
	t_env_lst	*del_node;

	if (del_lst == NULL)
		return ;
	while (del_lst)
	{
		del_node = del_lst;
		del_lst = del_node->nx;
		ft_free_envlst_node(del_node);
	}
}
