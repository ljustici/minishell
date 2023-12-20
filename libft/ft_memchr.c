/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:22:27 by ljustici          #+#    #+#             */
/*   Updated: 2022/09/18 14:44:09 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*char_s;

	char_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)c == char_s[i])
			return ((void *)char_s + i);
		i++;
	}
	return (0);
}
