/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:00:34 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/01 21:51:10 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   **  ONLY CHECKS CTRL+C, NOT CTRL+\ (TO IGNORE) **
 * 
 * 	if (SIGINT == sig)
	{
		g_listen = 1;
		rl_on_new_line();
		rl_redisplay();
	//	rl_replace_line("   ", 0);
		ft_putstr_fd("   ", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	//	rl_redisplay();
	}
 * 
 * @param sig      The signal (SIGINT, in this case)
 * @param info 
 * @param context 
 */
void	ft_handler(int sig, siginfo_t *info, void *context)

{
	(void)info;
	(void)context;
	if (SIGINT == sig)
	{
		g_listen = 1;
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("   ", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
}

/**
 * @brief    **  IT'S NOT A SIGNAL, ONLY A SPECIAL CHARACTER **
 * 	-	rl_on_new_line(); // parece que limpia el búffer
 *	-	rl_redisplay();	// y parece que se pone al inicio de la misma línea
 * 
 * @param data 
 */
void	ft_ctrl_d(t_msh *data)
{
	if (!data->pipeline)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("exit\n", 1);
		rl_clear_history();
		ft_env_lstclear(data->env_lst);
		exit(EXIT_SUCCESS);
	}
}
