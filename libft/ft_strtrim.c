/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 06:46:52 by ljustici          #+#    #+#             */
/*   Updated: 2022/09/18 14:45:30 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	size;
	char	*result;

	size = ft_strlen(s1);
	start = 0;
	while (start < size)
	{
		if (!ft_strchr(set, s1[start]))
			break ;
		start++;
	}
	end = size - 1;
	while (end >= 0)
	{
		if (!ft_strchr(set, s1[end]))
			break ;
		end--;
	}
	end++;
	result = ft_substr(s1, start, end - start);
	return (result);
}
