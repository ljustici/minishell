/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_dupl_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:16:37 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/11/08 15:40:57 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**   CORREGIRRRRRRRR PARA QUE LA PRIMERA VEZ NO COJA EL VALOR DE OLDPWD
 * @brief    DUPLICS the environment vars to a linked list
 * 		   (BEWARE OF THIS: the '=' caracter is CONTROLED, not stored)
 * 
 * @param envp 
 */
void	ft_duplic_envp(t_msh *data, char **envp)
{
	int			i;
	char		**tmp_env;
	
	i = -1;
	while (envp[++i])
	{
		tmp_env = ft_2rows_split(envp[i], '=');
		if (!tmp_env)
			return ;
		if (ft_strcmp(tmp_env[0], "OLDPWD") == 0)
			ft_free_null_void_return(&tmp_env[1]);
		if (ft_strchr(envp[i], '=') && ft_strcmp(tmp_env[0], "OLDPWD") != 0)
			ft_env_lstadd_back(data, ft_env_lst_new(tmp_env, 1));
		else
			ft_env_lstadd_back(data, ft_env_lst_new(tmp_env, 0));
		ft_freedom(tmp_env);
	}
}


/**
 * @brief       **** BUILTS A NODE WITH THE PARAMTRS INFO ****
 * 		Detects if the name cointains forbidden chars:
 * 			- 1st position of 'nm': only letters or '_'
 * 			- rest positions of 'nm': only numbers or letters or '_'
 * @param tmp_env 
 * @param equal 
 * @return t_env_lst* 
 */
t_env_lst	*ft_env_lst_new(char **tmp_env, int equal)
{
	t_env_lst	*node;

	node = (t_env_lst *)malloc(sizeof(t_env_lst));
	node->nm = ft_strdup(tmp_env[0]);
	node->val = ft_strdup(tmp_env[1]);
	node->equal = equal;
	node->nx = NULL;
	if (ft_env_forbidden_chars(node->nm))
	{
		ft_printf("export: `%s': not a valid identifier\n", node->nm);
		ft_free_envlst_node(node);
		return (NULL);
	}
	return (node);	
}
