/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils_free_null.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:54:51 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/11 15:05:06 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_null_void_return(char **str)
{
	if (*str != NULL)
	{
		ft_bzero(*str, ft_strlen(*str));
		free(*str);
		*str = NULL;
	}
}

char	*ft_free_null_no_void_return(char *str)
{
	if (str != NULL)
	{
		ft_bzero(str, ft_strlen(str));
		free(str);
		str = NULL;
	}
	return (str);
}

char	**ft_freedom(char **matrix)
{
	size_t	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i])
		{
			ft_bzero(matrix[i], ft_strlen(matrix[i]));
			free(matrix[i]);
			matrix[i] = NULL;
			i++;
		}
		free(matrix);
		matrix = NULL;
	}
	return (matrix);
}
