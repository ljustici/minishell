/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 01:32:58 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/11 13:10:52 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* char	*ft_strdup(const char *src)
{
	char	*src_copy;
	int		i;

	i = 0;
	src_copy = (char *)malloc(ft_strlen(src) + 1);
	if (!src_copy)
		return (0);
	while (src[i])
	{
		src_copy[i] = src[i];
		i++;
	}
	src_copy[i] = '\0';
	return (src_copy);
} */

char	*ft_strdup(const char *s1)
{
	char		*dst;
	size_t		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dst = (char *)ft_calloc((len + 1), sizeof(char));
	if (!dst)
		return (NULL);
	ft_memmove(dst, s1, len);
	dst[len] = '\0';
	return (dst);
}
