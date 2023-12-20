/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_flag_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:18:20 by ljustici          #+#    #+#             */
/*   Updated: 2022/09/21 15:38:23 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str, int fd)
{
	int	n;

	if (!str)
	{
		ft_putstr_fd("(null)", fd);
		n = 6;
	}
	else
	{
		ft_putstr_fd(str, fd);
		n = ft_strlen(str);
	}
	return (n);
}

int	ft_putnbr(int n, int fd)
{
	int		length;
	char	*str;

	str = ft_itoa(n);
	length = ft_putstr(str, fd);
	free(str);
	return (length);
}

int	ft_puthex(unsigned long long nbr, char *base, int fd)
{
	int	length;

	length = 0;
	if (nbr < 0)
		nbr = (unsigned int)nbr;
	if (nbr >= 16)
		length += ft_puthex(nbr / 16, base, fd);
	length += ft_putchar(base[nbr % 16], fd);
	return (length);
}

int	ft_putpt(void *pt, int fd)
{
	int	length;

	length = 0;
	length += ft_putstr("0x", fd);
	length += ft_puthex((unsigned long long)pt, "0123456789abcdef", fd);
	return (length);
}

int	ft_putunbr(unsigned int n, int fd)
{
	int	length;

	length = 0;
	if (n < 0)
		n = (unsigned int)n;
	if (n >= 10)
		length += ft_putunbr(n / 10, fd);
	length += ft_putchar((n % 10) + '0', fd);
	return (length);
}
