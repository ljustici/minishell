/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin_executor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:21:55 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/01/23 23:44:08 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  BEWARE OF THIS !!! DO YOU HAVE THE CONVENIENT PERMISSIONS
 * 			TO EXECUTE THE COMMAND ???
 * 
 * RAZONAMTO: cada comando tiene una lista de redirs:
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
	comprobar qué funciones de la librería <sys/stat.h> podemos usar
*/
static int	ft_check_permissions(t_msh *data, char *dir)
{
	struct stat	st;

	if (stat(dir, &st) == 0) // está comprobando si existe el archivo
	{
		if (st.st_mode & S_IXUSR) // está comprobando si tiene permisos de ejecución
			return (0);
		else
		{
			ft_error(data, dir, "Permission denied");
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
 * 	>> env    -> bash admits both LOWERS & UPPERS
 *  >> export -> bash admits only LOWERS, not UPPERS
 *  >> unset  -> bash admits only LOWERS, not UPPERS
 *  >> pwd    -> bash admits both LOWERS & UPPERS
 *  >> cd     -> bash admits both LOWERS & UPPERS (but do nothing if UPPERS)
 *  >> echo   -> bash admits both LOWERS & UPPERS
 *  >> exit   -> bash admits only LOWERS, not UPPERS
 * 
 *  BEWARE OF THIS !!! >>> In case of absolute path, 
 * 		¿¿¿ what should be executed, the REAL builtin or ours ???
 * 	ANSWER >>> the builtins don't have absolute path, 
 *             they comunicate to the shell directly
 * 
 * @brief   ** VERSIÓN 2.0 -> PASANDO UN CMD_NODO (PRESENCIA DE PIPES)
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
	if (ft_check_permisions(data, cmd_nd->c_args[0]) == 0)
		ft_cmd_analyzer(data, cmd, cmd_nd);
}
