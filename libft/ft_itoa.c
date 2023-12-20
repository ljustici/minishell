/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 10:25:55 by ljustici          #+#    #+#             */
/*   Updated: 2022/09/18 14:43:36 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	long	n_long;
	int		n_len;

	n_len = 0;
	n_long = n;
	if (n_long <= 0)
		n_len = 1;
	if (n_long < 0)
		n_long = -n_long;
	while (n_long > 0)
	{
		n_long /= 10;
		n_len++;
	}
	return (n_len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	n_long;
	int		i;
	int		n_len;
	int		negative;

	n_len = ft_numlen(n);
	str = ft_calloc(n_len + 1, sizeof(char));
	if (!str)
		return (0);
	n_long = n;
	negative = 0;
	if (n_long < 0)
	{
		n_long = -n_long;
		str[0] = '-';
		negative = 1;
	}
	i = -1;
	while (++i < n_len - negative)
	{
		str[n_len - 1 - i] = '0' + n_long % 10;
		n_long /= 10;
	}
	return (str);
}
