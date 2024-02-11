/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:17:09 by roruiz-v          #+#    #+#             */
/*   Updated: 2024/02/11 15:15:31 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_str_digits(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	if (str[++i] == '+')
		;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	ft_matrix_len(char **str)
{
	int	i;

	if (!str)
		return (-42);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @brief  Builds a 2 rows matrix, dividing by 1st coincidence of 'c'
 * 			If there's no 'c', then the second row = NULL.
 * @param str 		    The string to be divided
 * @param c 		    The char to be finded to do the division
 * @return char**       
 */
char	**ft_2rows_split(char *str, char c)
{
	size_t	i;
	char	**matrix;

	i = -1;
	matrix = NULL;
	if (!str || ft_strlen(str) == 0)
		return (NULL);
	matrix = ft_calloc(3, sizeof(char *));
	if (!matrix)
		return (NULL);
	while (str[++i] && str[i] != c)
		;
	matrix[0] = ft_substr(str, 0, i);
	if (!matrix[0])
		return (ft_freedom(matrix), NULL);
	if (str[i] == c && i < ft_strlen(str) - 1)
	{
		matrix[1] = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
		if (!matrix[1])
			return (ft_freedom(matrix), NULL);
	}
	else if (str[i] != c || (str[i] == c && i == ft_strlen(str) - 1))
		matrix[1] = ft_calloc(1, sizeof(char));
	return (matrix);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	s = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(*s));
	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	if (s1)
	{
		while (s1[i])
		{
			s[i] = s1[i];
			i++;
		}
		ft_free_null_void_return(&s1);
	}
	if (s2)
		while (s2[++j])
			s[i++] = s2[j];
	return (s);
}

int	ft_detect_forbidden_chars(char *name)
{
	int	i;

	i = 0;
	if (!((name[i] >= 'A' && name[i] <= 'Z')
			|| (name[i] >= 'a' && name[i] <= 'z')
			|| (name[i] == '_')))
		return (1);
	while (name[++i])
	{
		if (!((name[i] >= 'A' && name[i] <= 'Z')
				|| (name[i] >= 'a' && name[i] <= 'z')
				|| (name[i] >= '0' && name[i] <= '9')
				|| (name[i] == '_')))
			return (1);
	}
	return (0);
}
