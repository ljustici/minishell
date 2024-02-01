/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:06:20 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/01 17:07:22 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_syntax_token(t_msh *data, char *token, int error)
{
	data->error = error;
	ft_putstr_fd("msh: ", 2);
	if (error == ERROR_SYNTAX_UNEXPECTED_TOKEN)
	{
		ft_putstr_fd(": syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putstr_fd("'\n", 2);
		data->exit_code = 258;
	}
	if (error == ERROR_MALLOC_ERROR)
	{
		ft_putstr_fd("Malloc error\n", 2);
	}
	if (error == ERROR_QUOTE)
	{
		ft_putstr_fd(": syntax error near unexpected quote\n", 2);
		data->exit_code = 258;
	}
}
