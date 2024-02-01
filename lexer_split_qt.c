/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_qt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:39:05 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/01 16:36:42 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_quoted_token(t_lexer lex, size_t *i, int *j, int f_letter_pos)
{
	if ((lex.s[*i] == '\'' || lex.s[*i] == '\"') && (is_spnltab(lex.s[*i
			- 1]) || is_first_quote(lex.s, *j, lex.s[*i])))
	{
		f_letter_pos = *i;
		span_until_quote(lex.s, i, lex.s[*i]);
		span_tail_str(lex.s, i);
		lex.tokens[*j] = ft_substr(lex.s, f_letter_pos, (*i - f_letter_pos)
				+ 1);
		if (!lex.tokens[*j])
			return (0); //malloc error
		*j = *j + 1;
	}
	return (1);
}

/**
 * Get position of char c in string s starting from start.
*/
int	get_char_pos(const char *s, size_t start, char c)
{
	size_t	i;

	i = start;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/**
 * Spans all the characters that belong to a variable. Only 
 * letters, numbers and underscores are allowed. Also $$ and
 * $? and all the numbered variables ($0, $1, etc).
*/
void	span_var_in_dqt(const char *s, size_t *i, size_t end_qt)
{
	(*i)++;
	if (s[*i] == '$' || ft_isdigit(s[*i]) || s[*i] == '?')
	{
		(*i)++;
		return ;
	}
	while (*i < end_qt && (ft_isalnum(s[*i]) == 1 || s[*i] == '_'))
		(*i)++;
}

int	add_token(t_lexer lex, int f_letter_pos, size_t i, int *j)
{
	if (i - f_letter_pos > 0)
	{
		lex.tokens[*j] = ft_substr(lex.s, f_letter_pos, i - f_letter_pos);
		if (!lex.tokens[*j])
			return (0);
		(*j)++;
	}
	return (1);
}

/**
 * Checks if a character is a double quote and then obtains the
 * position of the closing one. Spans until this position, assigning
 * string tokens and variable tokens, if there are any.
 * Also spans the characters found after the closing double quote
 * if they are not separators and adds them to the last token.
*
int	assign_doubleqt_token(t_lexer lex, size_t *i, int *j, int f_letter_pos)
{
	size_t	end_qt;

	if (lex.s[*i] == '\"' && ((is_spnltab(lex.s[*i
		- 1])) || is_first_quote(lex.s, *j, lex.s[*i])))
	{
		end_qt = get_char_pos(lex.s, *i + 1, lex.s[*i]);
		while (*i <= end_qt)
		{
			f_letter_pos = *i;
			if (is_var_in_dqt(lex.s, *i) && *i <= end_qt)
			{
				span_var_in_dqt(lex.s, i, end_qt);
				if (add_token(lex, f_letter_pos, *i, j) == 0)
					return (0);
			}
			else if (*i <= end_qt)
			{
				while (lex.s[*i] && !is_var_in_dqt(lex.s, *i) && *i <= end_qt)
					(*i)++;
				span_tail_str(lex.s, i);
				if (add_token(lex, f_letter_pos, *i, j) == 0)
					return (0);
			}
		}
	}
	return (1);
}*/
