/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:52:44 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/03 18:38:44 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_tokens(const char *str)
{
	int	i;
	int	is_first_letter;
	unsigned long	j;

	j = 0;
	i = 0;
	is_first_letter = 0;
	while (str[j])
	{
		handle_count_quote(str, &j, &i);
		if (is_metacharacter(str[j]) == 1)
		{	
			i++;
			is_first_letter = 0;
			if (is_metacharacter(str[j + 1]) == 1)
				j++;
		}
		else if (should_split(str[j]) != 1 && is_first_letter == 0)
		{
			is_first_letter = 1;
			i++;
		}
		else if (should_split(str[j]) == 1 && is_first_letter == 1)
			is_first_letter = 0;
		j++;
	}
	return (i);
}

int assign_token(char **result, const char *s, size_t *i, int *j, int f_letter_pos)
{
	printf("[Llega a assign_token]\n");
	if (is_metacharacter(s[*i]) && is_metacharacter(s[*i + 1]))
		*i = *i + 1;
	*i = *i + 1;
	add_token(s, result, f_letter_pos, *i, j);
	return (1);
}


/*int assign_token(char **result, const char *s, size_t *i, int *j, int f_letter_pos)
{
	if (is_metacharacter(s[*i]))
	{
		if (is_metacharacter(s[*i + 1]))
		{
			result[*j] = ft_substr(s, f_letter_pos, 2);
			*i = *i + 1;
		}
		else
			result[*j] = ft_substr(s, f_letter_pos, 1);
	}
	else
		result[*j] = ft_substr(s, f_letter_pos, (*i - f_letter_pos) + 1);
	if (!result[*j])
		return (0);
	printf("[j: %i --> %s]\n", *j, result[*j]);
	*j = *j + 1;
	return (1);
}*/

int	fill_tokens(char **result, const char *s)
{
	int		j;
	int		f_letter_pos;
	size_t	i;

	f_letter_pos = -1;
	j = 0;
	i = 0;
	while (i <= ft_strlen(s))
	{
		printf("f_letter_pos: %i para i: %zu\n", f_letter_pos, i);
		if (assign_quoted_token(result, s, &i, &j, f_letter_pos) == 0
				|| assign_doubleqt_token(result, s, &i, &j, f_letter_pos) == 0)
			return (0); //malloc error
		if ((should_split(s[i]) != 1 && f_letter_pos == -1) || is_metacharacter(s[i]) == 1)
			f_letter_pos = i;
		if (s[i] && (should_split(s[i]) == 1 || should_split(s[i + 1])) && f_letter_pos >= 0)
		{
			printf("c to split: %c en pos %zu y f_let: %i\n", s[i], i, f_letter_pos);
			if (assign_token(result, s, &i, &j, f_letter_pos) == 0)
				return (0); //malloc error
			f_letter_pos = -1;
		}
		else if (i == ft_strlen(s) && f_letter_pos >= 0 && f_letter_pos < (int)i - 1)
		{
			printf("c to split: %c en pos %zu y f_let: %i\n", s[i], i, f_letter_pos);
			if (assign_token(result, s, &i, &j, f_letter_pos) == 0)
				return (0); //malloc error
			f_letter_pos = -1;
		}
		i++;
	}
	result[j] = 0;
	return (1);
}

char **split_by_metachar(char const *s)
{
    int		n_of_w;
	int		correct;
	char	**result;

	n_of_w = count_tokens(s);
	printf("n of w: %i\n", n_of_w);
	result = (char **)ft_calloc(n_of_w + 1, sizeof(char *));
	if (!result)
		return (0);
	correct = fill_tokens(result, s);
	if (!correct)
	{
		printf("nop\n");
		ft_free_array(result);
		return (0);
	}
	return (result);
}
