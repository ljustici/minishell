/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:52:17 by ljustici          #+#    #+#             */
/*   Updated: 2023/08/16 15:56:52 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	ft_check_flag(char const flag, va_list args, int fd)
{
	int	length;

	length = 0;
	if (flag == 'c')
		length = ft_putchar(va_arg(args, int), fd);
	else if (flag == 's')
		length = ft_putstr(va_arg(args, char *), fd);
	else if (flag == 'p')
		length = ft_putpt(va_arg(args, void *), fd);
	else if (flag == 'd')
		length = ft_putnbr(va_arg(args, unsigned int), fd);
	else if (flag == 'i')
		length = ft_putnbr(va_arg(args, int), fd);
	else if (flag == 'u')
		length = ft_putunbr(va_arg(args, unsigned int), fd);
	else if (flag == 'X')
		length = ft_puthex(va_arg(args, unsigned int), "0123456789ABCDEF", fd);
	else if (flag == 'x')
		length = ft_puthex(va_arg(args, unsigned int), "0123456789abcdef", fd);
	else if (flag == '%')
		length = ft_putchar('%', fd);
	return (length);
}

int	ft_printf(int fd, char const *format, ...)
{
	va_list	args;
	int		i;
	int		length;

	va_start(args, format);
	i = 0;
	length = 0;
	if (!format)
		return (0);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			length += ft_check_flag(format[++i], args, fd);
		else
			length += ft_putchar(format[i], fd);
		i++;
	}
	va_end(args);
	return (length);
}
