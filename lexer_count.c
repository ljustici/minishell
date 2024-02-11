/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:25:59 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/11 12:39:44 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	span_to_next_first_letter(const char *str, size_t *j,
	int *i, int *is_first_letter)
{
	if (should_split(str[*j]) != 1 && *is_first_letter == 0)
	{
		*is_first_letter = 1;
		(*i)++;
	}
	if (is_first_quote(str, *j, str[*j]))
		handle_count_quote(str, j, i);
	if (is_metacharacter(str[*j]) == 1)
	{
		(*i)++;
		*is_first_letter = 0;
		if (is_metacharacter(str[(*j) + 1]) == 1)
			(*j)++;
	}
	if (should_split(str[*j]) == 1 && *is_first_letter == 1)
		*is_first_letter = 0;
}

/**
 * Counts the number of token in a string by delimiting character:
 * - First letter
 * - Quotes
 * - Separating character
 * It doesn't count variables inside double quotes.
*/
int	count_tokens(const char *str)
{
	int				i;
	int				is_first_letter;
	unsigned long	j;

	j = 0;
	i = 0;
	is_first_letter = 0;
	while (j < ft_strlen(str))
	{
		span_to_next_first_letter(str, &j, &i, &is_first_letter);
		j++;
	}
	return (i);
}
