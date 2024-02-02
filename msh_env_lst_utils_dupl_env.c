/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_lst_utils_dupl_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:16:37 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/01 17:10:48 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**   
 * @brief    * DUPLICS the environment vars to a linked list * 
 *  BEWARE OF THIS: 
 * 		- the '=' caracter is CONTROLED, not stored)
 * 		- OLDPWD value must be NULL at the beginning
 * 		- SHLVL must increase its value at the beginning
 * 
 * @param envp 
 */
void	ft_duplic_envp(t_msh *data, char **envp)
{
	int		i;
	char	**tmp_env;
	char	*shlvl;

	i = -1;
	while (envp[++i])
	{
		tmp_env = ft_2rows_split(envp[i], '=');
		if (!tmp_env)
			return ;
		if (ft_strcmp(tmp_env[0], "OLDPWD") == 0)
			ft_free_null_void_return(&tmp_env[1]);
		else if (ft_strcmp(tmp_env[0], "SHLVL") == 0)
		{
			shlvl = ft_itoa(ft_atoi(tmp_env[1]) + 1);
			ft_free_null_void_return(&tmp_env[1]);
			tmp_env[1] = ft_strdup(shlvl);
			ft_free_null_void_return(&shlvl);
		}
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
	if (ft_detect_forbidden_chars(node->nm))
	{
		ft_putstr("export: ", 2);
		ft_putstr(node->nm, 2);
		ft_putstr(": not a valid identifier\n", 2);
		ft_free_envlst_node(node);
		return (NULL);
	}
	return (node);
}
