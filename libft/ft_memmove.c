/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:33:38 by ljustici          #+#    #+#             */
/*   Updated: 2022/09/18 14:44:20 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_char;
	const unsigned char	*src_char;

	if (!dst && !src)
		return (0);
	if (dst > src)
	{
		dst_char = dst + len;
		src_char = src + len;
		while (len-- > 0)
		{
			*--dst_char = *--src_char;
		}
	}
	else
	{
		dst_char = dst;
		src_char = src;
		while (len-- > 0)
		{
			*dst_char++ = *src_char++;
		}
	}
	return ((void *)dst);
}
