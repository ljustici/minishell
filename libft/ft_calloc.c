/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 01:13:51 by ljustici          #+#    #+#             */
/*   Updated: 2022/09/18 14:43:26 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*contiguous;
	size_t	total_size;

	total_size = count * size;
	if (total_size < count && total_size < size)
		return (0);
	contiguous = malloc(total_size);
	if (!contiguous)
		return (0);
	ft_bzero(contiguous, total_size);
	return (contiguous);
}
