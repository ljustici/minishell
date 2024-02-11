/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:52:44 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/11 12:31:53 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_token(t_lexer lex, size_t *i, int *j, int f_letter_pos)
{
	if (is_metacharacter(lex.s[*i]) && is_metacharacter(lex.s[*i + 1]))
		*i = *i + 1;
	*i = *i + 1;
	if (add_token(lex, f_letter_pos, *i, j) == 0)
		return (0);
	if (*i > 0)
		*i = *i - 1;
	return (1);
}

static	int	is_first_char_in_token(t_lexer lex, size_t i, int f_letter_pos)
{
	if ((should_split(lex.s[i]) != 1 && f_letter_pos
			== -1) || is_metacharacter(lex.s[i]) == 1)
		return (1);
	return (0);
}

/**
* Checks if a character is a separator:
*
* - Opening double quotes or simple quotes. Any characters enclosed or
* following quotes are part of the same token, therefore they're spanned.
* - Spaces, tabs, new lines, pipes, redirections.
* - A first character that is not any of the above.
* It then saves the position of the character and spans until the next
* character of any of those types.
* A token is saved from the saved position to the next position found.
*/
int	check_and_fill(t_lexer lex, size_t *i, int *j, int *f_letter_pos)
{
	if (is_first_quote(lex.s, *i, lex.s[*i]))
	{
		if (*f_letter_pos == -1)
			*f_letter_pos = *i;
		span_until_quote(lex.s, i, lex.s[*i]);
		span_tail_str(lex.s, i);
		*i = *i - 1;
	}
	if (is_first_char_in_token(lex, *i, *f_letter_pos) == 1)
		*f_letter_pos = *i;
	if (lex.s[*i] && (should_split(lex.s[*i]) == 1 || should_split(lex.s[*i
					+ 1])) && *f_letter_pos >= 0)
	{
		if (assign_token(lex, i, j, *f_letter_pos) == 0)
			return (0);
		*f_letter_pos = -1;
	}
	else if (*i == ft_strlen(lex.s) && *f_letter_pos >= 0
		&& *f_letter_pos < (int)*i - 1)
	{
		if (assign_token(lex, i, j, *f_letter_pos) == 0)
			return (0);
		*f_letter_pos = -1;
	}
	return (1);
}

int	fill_tokens(char **result, const char *s, t_msh *data)
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
		if (check_and_fill(lex, &i, &j, &f_letter_pos) == 0)
		{
			error_syntax_token(data, "", ERROR_MALLOC_ERROR);
			return (0);
		}
		i++;
	}
	lex.tokens[j] = 0;
	return (1);
}

char	**split_by_metachar(char const *s, t_msh *data)
{
	int		n_of_w;
	int		correct;
	char	**result;

	n_of_w = count_tokens(s);
	result = (char **)ft_calloc(n_of_w + 1, sizeof(char *));
	if (!result)
	{
		error_syntax_token(data, "", ERROR_MALLOC_ERROR);
		return (0);
	}
	correct = fill_tokens(result, s, data);
	if (!correct)
	{
		ft_free_array(result);
		return (0);
	}
	return (result);
}
