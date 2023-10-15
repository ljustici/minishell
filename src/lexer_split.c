/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:52:44 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/21 19:41:03 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int handle_count_quote(const char *str, unsigned long *j, int *i)
{
	//printf("init num %i\n", *i);
	if ((str[*j] == '\'' || str[*j] == '\"') && is_spnltab(str[*j - 1]))
	{
		
		*i = *i + 1;
		if (str[*j] == '\"')
		{
			while(str[++(*j)] != '\"')
			{
				//buscar separaciones
				if (str[*j] == '$')
					*i = *i + 1;
				//printf("while num %i\n", *i);
			}
		}
		if (str[*j] == '\'')
		{
			span_until_quote(str, j, str[*j]);
			//*j = *j + 1;
		}
		//printf("fin num %i\n", *i);
	}
	else
		return(1);
	return(0);
}

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
		if (handle_count_quote(str, &j, &i) == 0)
			i++;
		else if (is_metacharacter(str[j]) == 1)
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
	//printf("i:%i\n", i);
	return (i);
}

int assign_token(char **result, const char *s, size_t *i, int *j, int f_letter_pos)
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
}

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
		if (assign_quoted_token(result, s, &i, &j, f_letter_pos) == 0
				|| assign_doubleqt_token(result, s, &i, &j, f_letter_pos) == 0)
			return (0); //malloc error
		if ( (should_split(s[i]) != 1 && f_letter_pos == -1) || is_metacharacter(s[i]) == 1)
			f_letter_pos = i;
		if ((should_split(s[i]) == 1 || i == ft_strlen(s) || should_split(s[i + 1])) && f_letter_pos >= 0)
		{
			printf("c to split: %c en pos %zu\n", s[i], i);
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
	printf("%i\n", n_of_w);
	result = (char **)ft_calloc(n_of_w + 1, sizeof(char *));
	if (!result)
		return (0);
	correct = fill_tokens(result, s);
	if (!correct)
	{
		ft_free_array(result);
		return (0);
	}
	return (result);
}
