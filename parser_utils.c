/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:32:34 by ljustici          #+#    #+#             */
/*   Updated: 2024/01/29 14:28:21 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join_free(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	s = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(*s));
	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	if (s1)
	{
		while (s1[i])
		{
			s[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[++j])
		s[i++] = s2[j];
	return (s);
}

/*char	*clean_quotes(char *s, char q, int start, size_t end)
{
	char	**clean;
	char	*noqts;
	int		array_len;
	int		i;

	i = 0;
	clean = ft_split(ft_substr(s, start, end), q);
	printf("Clean %s\n", clean[0]);
	noqts = ft_calloc(1, sizeof(char *));
	array_len = ft_array_len(clean);
	while (i < array_len)
	{
		noqts = ft_join_free(noqts, clean[i]);
		i++;
	}
	ft_free_array(clean);
	return (noqts);
}*/

/**
 * Function that spans a token, splits it when it finds quotes and then
 * joins the resulting pieces together in a new token, without said quotes.
 * The quotes that must be trimmed are opening and closing quotes.
 * A quote is opening or closing if it belongs to a pair of quotes.
*/
char	*clean_quotes(char *s, char q)
{
	char	**clean;
	char	*noqts;
	int		array_len;
	int		i;

	i = 0;
	clean = ft_split(s, q);
	noqts = ft_calloc(1, sizeof(char *));
	array_len = ft_array_len(clean);
	while (i < array_len)
	{
		noqts = ft_join_free(noqts, clean[i]);
		i++;
	}
	ft_free_array(clean);
	return (noqts);
}

/**
 * Checks if a token has an opening quote and a closing quote
*/
int	has_qts(char *token, char q)
{
	int	i;
	int	qt;

	i = 0;
	qt = 0;
	while (token[i])
	{
		if (token[i] == q)
			qt++;
		i++;
	}
	return (qt);
}

size_t next_qt_pos(char *token, size_t start, size_t len, char qt)
{
	while(start < len && token[start] != qt)
		start++;
	return(start);
}

int	 should_clean_quotes(char *token, char **parsed)
{
	size_t	i;
	size_t	len;
	size_t	dqt;
	size_t	sqt;

	len = ft_strlen(token);
	dqt = 0;
	sqt = 0;
	i = 0;
	*parsed = ft_strdup(token);
	while (i < len)
	{
		printf("Inicio de loop:\n - dqt: %zu, sqt: %zu en char %c\n", dqt, sqt, token[i]);
		if (dqt == 2)
			dqt = 0;
		else if (token[i] == '\"' && sqt == 0)
			dqt++;
		if (sqt == 2)
			sqt = 0;
		else if (token[i] == '\'' && dqt == 0)
			sqt++;
		printf("Antes de limpieza:\n - dqt: %zu, sqt: %zu en char %c\n", dqt, sqt, token[i]);
		if (dqt == 1 || sqt == 0)
		{
			*parsed = clean_quotes(&(*parsed)[i], '\"');//, i, next_qt_pos(token, i, len, '\"'));
			return (1);
		}
		else if (dqt == 0 || sqt == 1)
		{
			*parsed = clean_quotes(&(*parsed)[i], '\''); //, i, next_qt_pos(token, i, len, '\''));
			return (1);
		}
	}
	return (0);
}

/**
 * A token is a variable if it only contains allowed
 * characters and is at least 2 characters long.
 * The variable might be contained inside double quotes,
 * or there might be quoted characters next to the variable,
 * but it can't be contained inside simple quotes.
*/
int	is_var(char *token)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(token);
	if (len > 1 && token[0] == '$' && (token[1] == '$'
			|| token[1] == '_' || ft_isalnum(token[1]) || token[1] == '?'))
	{
		span_var_in_dqt(token, &i, len);
		return (1);
	}
	else
		return (0);
	return (0);
}
