/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:26:32 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/01/19 16:23:10 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   * Searchs a environment var by its name & returns its value *
 *  
 *  BEWARE OF THAt: chmod -> rwx
 *      With x in 1 state, we can cd into de dir (not if it's 0) 
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
 * La función `stat` en C se utiliza para obtener información sobre
 * un archivo o directorio. Esta información se almacena en una
 * estructura de tipo `struct stat`.
 *
 * Para obtener los permisos de un directorio, se utiliza el campo
 * `st_mode` de la estructura `struct stat`. Este campo contiene
 * información sobre el tipo de archivo y los permisos de acceso.
 * 
 * Los permisos de acceso se representan como un número en formato octal,
 * donde cada dígito representa los permisos de un tipo de usuario:
 * el propietario del archivo, el grupo del archivo y otros usuarios.
 * Cada dígito puede ser un número de 0 a 7.
 * 
 * Para extraer los permisos del campo `st_mode`, se utiliza el operador
 * bitwise AND (`&`) con el número octal `0777`. Esto se hace porque los
 * permisos de acceso son los últimos 9 bits del campo `st_mode`,
 * y `0777` en octal es una máscara de bits que tiene los últimos 9 bits
 * establecidos en 1 y el resto en 0. Al hacer `st_mode & 0777`,
 * se obtienen solo los bits que representan los permisos de acceso.
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
 * @brief       *** POSSIBLY FINISHED ***
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
