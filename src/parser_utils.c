/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:32:34 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/20 19:29:57 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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


/**
 * Function that spans a token, splits it when it finds quotes and then
 * joins the resulting pieces together in a new token, without said quotes.
*/
char *clean_quotes(char *s, char q)
{
    char **clean;
    char *noqts;
    int array_len;
    int i;

    i = 0;
    clean = ft_split(s, q);
    array_len = ft_array_len(clean);
    noqts = NULL;
    while (i < array_len)
    {
        noqts = ft_join_free(noqts, clean[i]);
        i++;
    }
    ft_free_array(clean);
    printf(">>>%s\n", noqts);
    return(noqts);
}

/**
 * Checks if a token has an opening quote and a closing quote
*/
int has_qts(char *token, char q)
{
    int i;
    int qt;

    i = 0;
    qt = 0;
    while(token[i])
    {
        if (token[i] == q)
            qt++;
        i++;
    }
    return(qt);
}

/**
 * A token is a variable if it doesn't have quotes and only contains allowed
 * characters
*/
int is_var(char *token)
{
	size_t len;
	size_t i;

	i = 0;
	len = ft_strlen(token);
	if (token[0] == '$' && len > 1 && !has_qts(token, '\"') && !has_qts(token, '\''))
		span_var_in_dqt(token, &i, len);
	if (i == len)
		return(1);
	return (0);
}

/**
 * Checks if the characters form any of the following commands:
 * &
 * .
 * !!
 * ###
*/
int is_special_cmd_chars(char *token)
{
    size_t n;

    n = ft_strlen(token);
    if (n == 1 && (token[0] = '.' || token[0] == '&'))
        return(1);
    else if (n == 2 && token[0] == '!' && token[1] == '!')
        return(1);
    else if (n == 3 && token[0] == '#' && token[1] == '#'
        && token[2] == '#')
        return(1);
    return(0);
}