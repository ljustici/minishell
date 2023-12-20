/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 23:19:49 by ljustici          #+#    #+#             */
/*   Updated: 2022/09/18 14:45:16 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uns_s1;
	unsigned char	*uns_s2;

	if ((!s1 && !s2) || n == 0)
		return (0);
	uns_s1 = (unsigned char *)s1;
	uns_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n - 1 && uns_s1[i] != '\0' && uns_s1[i] == uns_s2[i])
		i++;
	return (uns_s1[i] - uns_s2[i]);
}
