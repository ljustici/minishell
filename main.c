/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/12/18 19:29:26 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_listen = 0;
 
/* static void	ft_leaks(void)
{
	system("leaks -q minishell");
} */

static void	ft_print_minishell(void)
{
	ft_putstr_fd(" \n", 1);
	ft_putstr_fd(BACK_BLUE BOLD "._ _ o._ o _|_  _|| \n", 1);
	ft_putstr_fd("| | ||| ||_\\| |}_|| \n" RESET, 1);
}

static void	ft_print_wellcome(void)
{
	ft_print_minishell();
	ft_putstr_fd(BLUE BOLD " \n", 1);
	ft_putstr_fd("                \\`'-. 					\n", 1);
	ft_putstr_fd("                 )  _`-. 					\n", 1);
	ft_putstr_fd("                : _   '  \\ 				\n", 1);
	ft_putstr_fd("                ; *` _.   `--._ 			\n", 1);
	ft_putstr_fd("                `-.-'          `-. 		\n", 1);
	ft_putstr_fd("                  |       `       `. 		\n", 1);
	ft_putstr_fd("     _  _         :.       .        \\ 	\n", 1);
	ft_putstr_fd("    (_)(_)        | \\  .   :   .-'   . 	\n", 1);
	ft_putstr_fd("   (_>()<_)       :  )-.;  ;  /      : 	\n", 1);
	ft_putstr_fd("    (_)(_)        :  ;  | :  :       ;-. 	\n", 1);
	ft_putstr_fd("      ||          ; /   : |`-:     _ `- )	\n", 1);
	ft_putstr_fd("    |\\||/|     ,-' /  ,-' ; .-`- .' `--' \n", 1);
	ft_putstr_fd("   __\\||/__    `--'   `---' `---' 		\n", 1);
	ft_putstr_fd(" \n" RESET, 1);
	ft_putstr_fd(GREEN BOLD "Welcome to msh_4.0\n", 1);
	ft_putstr_fd("	by <ljustici> && <roruiz-v>\n", 1);
	ft_putstr_fd(" \n" RESET, 1);
	ft_putstr_fd(YELLOW BOLD "	*****      ENJOY IT !!!     *****\n", 1);
	ft_putstr_fd(YELLOW BOLD "	*****   (& be empathic) :)  *****\n", 1);
	ft_putstr_fd(" \n" RESET, 1);
}

void	ft_init_msh_struct(t_msh *data)
{
	data->var_ = NULL;
	data->error = NO_ERROR;
	data->exit_code = 0;
	data->env_lst = NULL;
	data->cmd_lst = NULL;
	data->fd = 1;
	data->org_stdin = dup(STDIN_FILENO);
	data->org_stdout = dup(STDOUT_FILENO);
//	data->sig.sa_flags = SA_RESTART;
	data->sig.sa_sigaction = ft_handler;
	sigemptyset(&data->sig.sa_mask);
	data->sig.sa_flags = SA_NODEFER; // a qué inicializarlo ?
	if (sigaction(SIGINT, &data->sig, NULL) == -1)
		ft_error_signal(ERROR_SIGACTION_FAILURE);
}

/**
 * @brief  * BEWARE OF THIS!!! 
 * 	- Si no restauro el STDIN y el STDOUT, hace un exit del programa
 *  - No reiniciar data->exit_code a 0, porque si hago echo $? me mostraría siempre 0
 * @param data 
 */
void	ft_main_boucle(t_msh *data)
{
	data->pipeline = readline(BACK_RED GREEN BOLD ">>> msh_3.0$ " RESET);
	ft_ctrl_d(data);
	if (data->pipeline[0] != '\0')
	{
		if (g_listen == 1)
		{
			data->exit_code = 1;
			data->error = END;
		}
		else
		{
			ft_free_null_void_return(&data->var_);
			add_history(data->pipeline);
			data->var_ = ft_strdup(data->pipeline);
			ft_simple_lexer(data);
			ft_simple_parser(data);
			if (data->error == NO_ERROR)
				ft_executor(data);
		}
	}
	g_listen = 0;
	ft_free_null_void_return(&data->pipeline);
	ft_cmdclear(data);
	dup2(data->org_stdin, STDIN_FILENO);  	// restaura el STDIN
//	close(data->org_stdin);  // no, que se cierra la minishell
	dup2(data->org_stdout, STDOUT_FILENO); 	// restaura el STDOUT
//	close(data->org_stdout);  // no, que se cierra la minishell
	data->error = NO_ERROR;
}
/**
 * @brief 		****	MINISHELL    ****
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return int 
 */
int	main(int argc, char **argv, char **envp)
{
	t_msh	data;
	
//	atexit(ft_leaks);
	(void)argv;
	if (argc > 1)
		ft_error_start(argv[1], ERROR_START_NO_SUCH_FILE_OR_DIRECTORY);
	ft_init_msh_struct(&data);
	ft_duplic_envp(&data, envp);
	ft_print_wellcome();
	while (1)
		ft_main_boucle(&data);
	return (0);
}

	