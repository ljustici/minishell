/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:52:44 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/13 19:28:50 by ljustici         ###   ########.fr       */
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
			printf(">>>is meta letter: %c\n", str[j]);
			if (is_metacharacter(str[j + 1]) == 1)
				j++;
		}
		else if (should_split(str[j]) != 1 && is_first_letter == 0)
		{
			printf(">>>letter: %c\n", str[j]);
			is_first_letter = 1;
			i++;
		}
		else if (should_split(str[j]) == 1 && is_first_letter == 1)
			is_first_letter = 0;
		j++;
	}
	return (i);
}

int assign_token(t_lexer lex, size_t *i, int *j, int f_letter_pos)
{
	printf("[Llega a assign_token]\n");
	if (is_metacharacter(lex.s[*i]) && is_metacharacter(lex.s[*i + 1]))
		*i = *i + 1;
	*i = *i + 1;
	if (add_token(lex, f_letter_pos, *i, j) == 0)
		return(0);
	if (*i > 0)
		*i = *i - 1;
	printf("token: %s letter:%i num: %i\n", lex.tokens[*j - 1], f_letter_pos, *j - 1);
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

int check_and_fill(t_lexer lex, size_t *i, int *j, int *f_letter_pos)
{
	if (assign_quoted_token(lex, i, j, *f_letter_pos) == 0
			|| assign_doubleqt_token(lex, i, j, *f_letter_pos) == 0)
		return (0); //malloc error
	if ((should_split(lex.s[*i]) != 1 && *f_letter_pos == -1)
		|| is_metacharacter(lex.s[*i]) == 1)
		*f_letter_pos = *i;
	if (lex.s[*i] && (should_split(lex.s[*i]) == 1 || should_split(lex.s[*i + 1]))
		&& *f_letter_pos >= 0)
	{
		if (assign_token(lex, i, j, *f_letter_pos) == 0)
			return (0); //malloc error
		*f_letter_pos = -1;
	}
	else if (*i == ft_strlen(lex.s) && *f_letter_pos >= 0 && *f_letter_pos
		< (int)*i - 1)
	{
		if (assign_token(lex, i, j, *f_letter_pos) == 0)
			return (0); //malloc error
		*f_letter_pos = -1;
	}
	return(1);
}

int	fill_tokens(char **result, const char *s)
{
	int		j;
	int		f_letter_pos;
	size_t	i;
	t_lexer	lex;

	lex.tokens = result;
	lex.s = s;
	f_letter_pos = -1;
	j = 0;
	i = 0;
	while (i <= ft_strlen(s))
	{
		check_and_fill(lex, &i, &j, &f_letter_pos);
		i++;
	}
	lex.tokens[j] = 0;
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
