/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:20:28 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/11 15:10:53 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_listen = 0;

/*static void	ft_leaks(void)
{
	system("leaks -q minishell");
}*/

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
	data->shadow_pwd = NULL;
	data->echo = NULL;
	data->sig.sa_sigaction = ft_handler;
	sigemptyset(&data->sig.sa_mask);
	data->sig.sa_flags = SA_NODEFER;
	if (sigaction(SIGINT, &data->sig, NULL) == -1)
		ft_error_signal(ERROR_SIGACTION_FAILURE);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief  * 

 * @param data 
 */
void	ft_main_boucle(t_msh *data)
{
	data->pipeline = readline(">>> msh_4.0$ ");
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
			if (ft_lexer(data) == 0)
				if (data->error == NO_ERROR)
					ft_executor(data);
		}
	}
	g_listen = 0;
	ft_free_null_void_return(&data->pipeline);
	ft_cmdclear(data);
	dup2(data->org_stdin, STDIN_FILENO);
	dup2(data->org_stdout, STDOUT_FILENO);
	data->error = NO_ERROR;
}

/**
 * @brief 		****	MINISHELL    ****
 * 	//atexit(ft_leaks);
 * @param argc 
 * @param argv 
 * @param envp 
 * @return int 
 */
int	main(int argc, char **argv, char **envp)
{
	t_msh	data;

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
