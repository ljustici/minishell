/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 08:42:18 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/01 13:06:48 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *str, char c)
{
	int	i;
	int	is_first_letter;
	int	j;

	j = 0;
	i = 0;
	is_first_letter = 0;
	while (str[j])
	{
		if (str[j] != c && is_first_letter == 0)
		{
			is_first_letter = 1;
			i++;
		}
		else if (str[j] == c && is_first_letter == 1)
			is_first_letter = 0;
		j++;
	}
	return (i);
}

int	ft_fill_array(char **result, const char *s, char c)
{
	int		j;
	int		f_letter_pos;
	size_t	i;

	f_letter_pos = -1;
	j = 0;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && f_letter_pos == -1)
			f_letter_pos = i;
		else if ((s[i] == c || i == ft_strlen(s)) && f_letter_pos >= 0)
		{
			result[j] = ft_substr(s, f_letter_pos, i - f_letter_pos);
			if (!result[j])
				return (0);
			j++;
			f_letter_pos = -1;
		}
		i++;
	}
	result[j] = 0;
	return (1);
}

void	ft_free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
		free(str);
	str = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		n_of_w;
	int		correct;
	char	**result;

	n_of_w = ft_count_words(s, c);
	result = (char **)ft_calloc(n_of_w + 1, sizeof(char *));
	if (!result)
		return (0);
	correct = ft_fill_array(result, s, c);
	if (!correct)
	{
		ft_free_array(result);
		return (0);
	}
	return (result);
}
