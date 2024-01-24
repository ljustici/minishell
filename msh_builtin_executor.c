/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:21:55 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/01/24 20:26:36 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  BEWARE OF THIS !!! DO YOU HAVE THE CONVENIENT PERMISSIONS
 * 			TO EXECUTE THE COMMAND ???
 *
 *  **** chmod -> rwx
 * 
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
*/

/**
 * @brief 
 * 
 * Cada comando tiene una lista de redirs:
 * 	- cada nodo de redir va cambiando el STDIN/STDOUT del comando
 *  - el efecto conseguido es que sólo el último redir de cada natu
 * 		(entrada/salida) define en última instancia cuál será la
 * 		entrada/salida definitiva DE DICHO COMANDO.
 * 
 * @param data 
 * @param cmd_nd 
 */
static void	ft_redir_checker(t_msh *data, t_cmd *cmd_nd)
{
	t_rd	*rd_nd;

	rd_nd = cmd_nd->rds;
	while (rd_nd != NULL)
	{
		if (cmd_nd->rds != NULL && rd_nd->type == DIR)
			ft_redir_heredoc(data, cmd_nd, rd_nd);
		else if (cmd_nd->rds != NULL && rd_nd->type == SIR)
			ft_redir_infile(data, cmd_nd, rd_nd);
		else if (cmd_nd->rds != NULL && rd_nd->type == SOR)
			ft_redir_outfile(data, cmd_nd, rd_nd);
		else if (cmd_nd->rds != NULL && rd_nd->type == DOR)
			ft_redir_outfile(data, cmd_nd, rd_nd);
		rd_nd = rd_nd->nx;
	}
}

/* BEWARE OF THIS !!!
	comprobar qué funciones de la librería <sys/stat.h> podemos usar:
	- stat
	- lstat
	- fstat
*/
static int	ft_check_permissions(t_msh *data, t_cmd *cmd_nd)
{
	struct stat	st;

//	cwd = getcwd(NULL, 0);
	if (stat(ft_env_obtain_val(data, "PWD"), &st) == 0) // está comprobando si existe el archivo
	{
//		if (st.st_mode & S_IXUSR) // está comprobando si tiene permisos de ejecución
		if (st.st_mode & S_IRWXU) // está comprobando si tiene todos los permisos
		{
			printf("DEBUG: ft_check_permissions) st_mode = %d\n", st.st_mode);
			return (0);
		}
		else
		{
			printf("DEBUG: ft_check_permissions) st_mode = %d\n", st.st_mode);
			ft_error_cmds(data, cmd_nd, ERROR_NO_PERMISSION);
			return (1);
		}
	}
	return (0);
}

static void	ft_cmd_analyzer(t_msh *data, char *cmd, t_cmd *cmd_nd)
{
	if (ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "ENV") == 0)
		ft_builtin_env(data, cmd_nd);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_builtin_export(data, cmd_nd);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_builtin_unset(data, cmd_nd);
	else if (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "PWD") == 0)
		ft_builtin_pwd(data);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_builtin_cd(data, cmd_nd);
	else if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "ECHO") == 0)
		ft_builtin_echo(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_builtin_exit(data, cmd_nd);
	else
	{
		ft_find_cmd_path(cmd_nd, ft_find_env_paths(data));
		data->exit_code = ft_exec_external_cmd(data, cmd_nd);
	}
}

/**
 * @brief ** Checks if the cmd is a builtin or an external command **
 * 
 * 	>> env    -> bash admits both LOWERS & UPPERS
 *  >> export -> bash admits only LOWERS, not UPPERS
 *  >> unset  -> bash admits only LOWERS, not UPPERS
 *  >> pwd    -> bash admits both LOWERS & UPPERS
 *  >> cd     -> bash admits both LOWERS & UPPERS (but do nothing if UPPERS)
 *  >> echo   -> bash admits both LOWERS & UPPERS
 *  >> exit   -> bash admits only LOWERS, not UPPERS
 * 
 * @param data 
 * @param cmd 
 * @param tmp 
 */
void	ft_builtin_executor(t_msh *data, char *cmd, t_cmd *cmd_nd)
{
	if (cmd_nd->rds != NULL)
	{
		ft_redir_checker(data, cmd_nd);
		if (g_listen == 1 || data->error != NO_ERROR)
			return ;
	}
	if (!cmd)
		return ;
//	if (ft_check_permissions(data, cmd_nd) == 0) // tiene que hacerlo después, no antes
		ft_cmd_analyzer(data, cmd, cmd_nd);
}
