/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:06:20 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/15 14:11:32 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_syntax_token(char *token, int error)
{
	if (error == ERROR_SYNTAX_UNEXPECTED_TOKEN)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(": syntax error near unexpected token `", 2);
        ft_putstr_fd(token, 2);
        ft_putstr_fd("'\n", 2);
		exit(258);
	}
}
