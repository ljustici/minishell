/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils_str_cmp_equal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:58:49 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/11 15:05:39 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief  ** COMPARES IF A STR IS GREATER, EQUAL OR LESS THAN ANOTHER STR **
 * 
 * @param s1 
 * @param s2 
 * @return int returns 0 if they are equal,
 *             returns 1 if s1 is lexicographically greater than s2 (s1 > s2)
 *             returns -1 if s1 is lexicographically less than s2 (s2 > s1)
 */
int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1 && s2 && s1[i] && s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	if (s1[i])
		return (1);
	else if (s2[i])
		return (-1);
	return (0);
}

/**
 * @brief   ***** COMPARES IF TWO STRINGS ARE EXACTLY THE SAME  *****
 * 
 * @param s1 
 * @param s2 
 * @return int   returns 0 if they aren't equal
 *               returns 1 if they are equal * 
 */
int	ft_str_equal(char *s1, char *s2)
{
	int		i;

	i = -1;
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) == ft_strlen(s2))
	{
		while (s1[++i])
		{
			if (s1[i] != s2[i])
				return (0);
		}
		return (1);
	}
	return (0);
}
