/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:25:30 by ljustici          #+#    #+#             */
/*   Updated: 2024/01/27 13:24:24 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Spans the characters found after and end quote, as they should be part of the same token.
 * Stops when a separator character is found.
*/
void span_tail_str(const char *str, unsigned long *j)
{
	
	if (should_split(str[*j]) == 0)
	{
		//while(str[*j] && should_split(str[*j]) == 0)
		while((*j) < ft_strlen(str) && should_split(str[*j]) == 0)
			(*j)++;
	}
	//printf("tail: %c\n", str[*j]);
}

/**
 * Spans a token delimited by quotes, including the characters right after the
 * last quotes, except if it's a separating character.
*/
int handle_count_quote(const char *str, unsigned long *j, int *i)
{	
	(void)*i;
	if (str[*j] == '\"' || str[*j] == '\'')
	{
		span_until_quote(str, j, str[*j]);
		span_tail_str(str, j);
		//printf("' Llega hasta %lu\n", *j);
	}
	return(0);
}

/**
 * Checks if the character is a starting quote by counting the number of
 * quotes before and after.
*/
int is_first_quote(const char *s, unsigned long pos, char c)
{
	size_t i;
	int count;

	//write(1, "Llega\n", 6);
	if (!s)
		return(0);
	count = 0;
	if (c != '\'' && c != '\"')
		return(0); 
	if (pos == 0)
		return(1);
	i = pos;
	while(i < ft_strlen(s) && s[i])
	{
		if (s[i] == c)
			count++;
		i--;
	}
	if (count == 0 || count % 2 != 0)
	{
		i = pos + 1;
		while(i < ft_strlen(s))
		{
			if (s[i] == c)
				return(1);
			i++;
		}
	}
	return(0);
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
	int	i;
	int	is_first_letter;
	unsigned long	j;

	j = 0;
	i = 0;
	is_first_letter = 0;
	while (j < ft_strlen(str))
	{
		if (should_split(str[j]) != 1 && is_first_letter == 0)
		{
			is_first_letter = 1;
			i++;
		}
		if (is_first_quote(str, j, str[j]))
			handle_count_quote(str, &j, &i);
		if (is_metacharacter(str[j]) == 1)
		{	
			i++;
			is_first_letter = 0;
			if (is_metacharacter(str[j + 1]) == 1)
				j++;
		}
		if (should_split(str[j]) == 1 && is_first_letter == 1)
			is_first_letter = 0;
		j++;
	}
	return (i);
}

/**
 * Checks if a character between double quotes belongs to a variable.
*/
int is_var_in_dqt(const char *s, unsigned long pos)
{
	if (s[pos] == '$' && s[pos + 1])
	{
		if (ft_isalnum(s[pos + 1]) || s[pos + 1] == '_')
			return (1);
		else if (s[pos + 1] == '$' || s[pos + 1] == '?' || s[pos + 1] == '#')
			return (1);
	}
	return(0);	
}

int is_equal_after_var(const char *s, unsigned long pos)
{
	size_t prev;
	
	prev = pos - 1;
	if (s[pos] == '=')
	{
		while(!should_split(s[prev]) && s[prev] != '$')
			prev--;
		if (s[prev] == '$')
			return (1);
	}
	return (0);
}

/**
 * Counts the number of tokens inside double quotes. It counts variables and
 * not variables. The double quotes themselves are not variables and will be a
 * single token or part of a not-variable token. Variables are spanned so that
 * their characters won't be accounted for as part of not-variable tokens.
 * Not-variable tokens are also spanned, and only counted as a new token with
 * their first character. The first character of the first token will always be
 * a double quote. The first character of other not-variable tokens will always
 * be the first character found after a variable token.
*/
void count_dqt_tokens(const char *str, unsigned long *j, int *i)
{
	int is_plain;
	size_t end_qt;
	
	is_plain = 0;
	end_qt = get_char_pos(str, *j + 1, str[*j]);
	while(str[*j] && *j <= end_qt)
	{
		if (is_var_in_dqt(str, *j))
		{
			is_plain = 0;
			*i = *i + 1;
			span_var_in_dqt(str, j, end_qt);
		}
		else
		{
			if (is_plain == 0)
				*i = *i + 1;
			is_plain = 1;
			(*j)++;
		}
	}
}
