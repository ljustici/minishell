/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:52:44 by ljustici          #+#    #+#             */
/*   Updated: 2023/12/19 14:32:45 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int assign_token(t_lexer lex, size_t *i, int *j, int f_letter_pos)
{
	if (is_metacharacter(lex.s[*i]) && is_metacharacter(lex.s[*i + 1]))
		*i = *i + 1;
	*i = *i + 1;
	if (add_token(lex, f_letter_pos, *i, j) == 0)
		return(0);
	if (*i > 0)
		*i = *i - 1;
	//printf("token: %s letter:%i num: %i\n", lex.tokens[*j - 1], f_letter_pos, *j - 1);
	return (1);
}

/**
 * Checks if a character is a separator:
 * - Opening double quotes or simple quotes. Any characters enclosed or following quotes
 *   are part of the same token, therefore they're spanned.
 * - Spaces, tabs, new lines, pipes, redirections.
 * - A first character that is not any of the above.
 * It then saves the position of the character and spans until the next character
 * of any of those types.
 * A token is saved from the saved position to the next position found.
*/
int check_and_fill(t_lexer lex, size_t *i, int *j, int *f_letter_pos)
{	
	if (is_first_quote(lex.s, *i, lex.s[*i]))
	{
		if (*f_letter_pos == -1)
			*f_letter_pos = *i;
		span_until_quote(lex.s, i, lex.s[*i]);
		span_tail_str(lex.s, i);
	}
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
	//printf("n of w: %i\n", n_of_w);
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


/*
int	count_tokens(const char *str)
{
	int	i;
	int	is_first_letter;
	unsigned long	j;
	unsigned long	v;

	j = 0;
	i = 0;
	is_first_letter = 0;
	while (str[j])
	{
		if (is_first_quote(str, j, str[j]))
			handle_count_quote(str, &j, &i);
		else if (str[j] == '$')
		{
			v = j;
			span_var_in_dqt(str, &v, ft_strlen(str));
			if (v > j)
			{
				j = v;
				i++;
			}
			if (is_equal_after_var(str, j))
				i++;
		}
		else if (is_metacharacter(str[j]) == 1)
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
*/