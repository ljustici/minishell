/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_errors_start_and_signals.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:48:13 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/01 17:49:01 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief   ** IN CASE OF EXECUTE 'MINISHELL' WITH ARGMTS **
 * 
 * @param argv_1 
 * @param error 
 */
void	ft_error_start(char *argv_1, int error)
{
	if (error == ERROR_START_NO_SUCH_FILE_OR_DIRECTORY)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(argv_1, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

void	ft_error_signal(int error)
{
	if (error == ERROR_SIGACTION_FAILURE)
	{
		ft_putstr_fd("Sigaction failure\n", 2);
		exit(EXIT_FAILURE);
	}
}
