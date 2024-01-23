/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:26:32 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/01/23 19:14:37 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *  BEWARE OF THIS: chmod -> rwx
 * 	With r in 1 state, we can list the files in the dir
 *  With r in 0 state, we can't list the files in the dir
 *  With w in 1 state, we can create, delete or rename files in the dir
 *  With w in 0 state, we can't create, delete or rename files in the dir
 *  With x in 1 state, we can cd into de dir (not if it's 0)
 *  With x in 0 state, we can't cd into de dir (not if it's 1)
 * 
 *   0: ningún permiso (ni lectura, ni escritura ni ejecución)
 *   1: (001) permiso de ejecución
 *   2: (010) permiso de escritura
 *   4: (100) permiso de lectura
 *   3: (011) permiso de escritura y ejecución
 *   6: (110) permiso de lectura y escritura (no de ejecución)
 *   5: (101) permiso de lectura y de ejecución
 *   7: (111) todos los permisos
 * 
 *  Function "stat", from <sys/stat.h> library, obtains info about an
 *  especified file or directory and puts the info into de "st" struct.
 *  With "st.st_mode & 0777" we can extract the permissions of the dir
 *  from "st.st_mode". The permissions can be printed in octal format.
 * 

/**
 * @brief   * Searchs a environment var by its name & returns its value *
 *  
 * 
 * @param data 
 * @param env_nm 
 * @return char*   A allocated string or NULL if the var doesn't exist.
 */
char	*ft_env_obtain_val(t_msh *data, char *env_nm)
{
	char		*src_val;
	t_env_lst	*tmp;
	
	src_val = NULL;
	tmp = data->env_lst;
	if (!env_nm)
		return (NULL);
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->nm, env_nm) == 0)
		{
			src_val = ft_strdup(tmp->val);
			break ;
		}
		tmp = tmp->nx;
	}
	return (src_val);
}

/**
 * @brief   * Change the value of an env var by the 'str' parameter *
 * 
 * @param data 
 * @param nm_dst 
 * @param new_val 
 */
void	ft_env_change_val(t_msh *data, char *nm_dst, char *new_val)
{
	t_env_lst	*tmp;

	tmp = data->env_lst;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->nm, nm_dst) == 0)
		{
			ft_free_null_void_return(&tmp->val);
			tmp->val = ft_strdup(new_val);
			tmp->equal = 1;
			ft_free_null_void_return(&new_val);
			break ;
		}
		tmp = tmp->nx;
	}
}

/**
 * @brief       *** TO_DO: PERMISIONS MANAGEMENT ***
 * 
 *    >> cd .      --> do NOTHING
 *    >> cd ..     --> chdir to ONE_LEVEL_UP
 *    >> cd        --> chdir to HOME (/Users/roruiz-v)
 *    >> cd ~      --> chdir to HOME (/Users/roruiz-v)
 *    >> cd -      --> chdir to OLDPWD (& prints that path)
 *    >> cd /      --> chdir to ROOT (/)
 *    >> cd algo mas  --> treat the 1st argmt, ignore the rest
 * 
 * @param data 
 */
void	ft_builtin_cd(t_msh *data, t_cmd *cmd_nd)
{	
	if (cmd_nd->c_args[1])
	{
		if (!ft_isalnum(cmd_nd->c_args[1][0]))
		{
			if (ft_strcmp(cmd_nd->c_args[1], "-") == 0)
				ft_builtin_cd_oldpwd(data, cmd_nd);
			else if (ft_strcmp(cmd_nd->c_args[1], "~") == 0)
				ft_builtin_cd_without_args(data, cmd_nd, 0);
			else if (chdir(cmd_nd->c_args[1]) == 0)
			{
				ft_env_change_val(data, "OLDPWD", ft_env_obtain_val(data, "PWD"));
				ft_env_change_val(data, "PWD", getcwd(NULL, 0));
			}
			else
				ft_error_cd(data, cmd_nd, ERROR_CHDIR_FAILURE);
		}
		else
			ft_builtin_cd_down(data, cmd_nd);
	}
	else
		ft_builtin_cd_without_args(data, cmd_nd, 1);
}
