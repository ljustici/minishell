/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 01:49:30 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/03 10:17:55 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	size_s2;
	size_t	size_s1;
	char	*result;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	result = (char *)malloc(size_s1 + size_s2);
	if (!result)
		return (0);
	i = size_s1 + size_s2;
	result[i] = '\0';
	while (size_s2 > 0)
		result[--i] = s2[--size_s2];
	while (size_s1 > 0)
		result[--i] = s1[--size_s1];
	return (result);
}
