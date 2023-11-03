/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_count_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:25:30 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/03 18:52:36 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Checks if a quote is the first character or if there is a 
 * separator character preceeding it.
*/
int is_start_of_quote(const char *s, unsigned long pos)
{
	if ((s[pos] == '\'' || s[pos] == '\"') && (is_spnltab(s[pos - 1]) || pos == 0))
		return (1);
	return(0);
}

/**
 * Checks if a character between double quotes belongs to a variable.
*/
int is_var_in_dqt(const char *s, unsigned long pos)
{
	if (s[pos] == '$')
	{
		if (s[pos + 1] && (ft_isalnum(s[pos + 1]) || s[pos + 1] == '_'))
			return (1);
		else if (s[pos + 1] == '$' || s[pos + 1] == '?')
			return (1);
	}
	return(0);	
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

/*void count_dqt_tokens(const char *str, unsigned long *j, int *i)
{
	int is_plain;
	
	is_plain = 1;
	while(str[*j] && str[++(*j)] != '\"')
	{
		if (is_var_in_dqt(str, *j))
		{
			is_plain = 0;
			*i = *i + 1;
			printf("letra en var: %c numero: %zu token numero: %i\n", str[*j], *j, *i);
		}
		else if (!is_var_in_dqt(str, *j) && is_plain == 0)
		{
			is_plain = 1;
			*i = *i + 1;
			printf("letra: %c token numero: %i\n", str[*j], *i);
		}
	}
}*/

/**
 * Spans the characters found after and end quote, as they should be part of the same token.
 * Stops when a separator character is found.
*/
void span_tail_str(const char *str, unsigned long *j)
{
	if (should_split(str[*j]) == 0)
	{
		while(str[*j] && should_split(str[*j]) == 0 && !is_var_in_dqt(str, *j))
			(*j)++;
	}
}

int handle_count_quote(const char *str, unsigned long *j, int *i)
{	
	//printf("init c %c y j %lu\n", str[*j], *j);
	if (is_start_of_quote(str, *j))
	{
		if (str[*j] == '\"')
		{
			count_dqt_tokens(str, j, i);
			span_tail_str(str, j);
			printf("\" Llega hasta %lu\n", *j);
		}
		if (str[*j] == '\'')
		{
			span_until_quote(str, j, str[*j]);
			span_tail_str(str, j);
			printf("' Llega hasta %lu\n", *j);
			//*j = *j + 1;
		}
	}
	else
		return(1);
	return(0);
}
