/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:32:34 by ljustici          #+#    #+#             */
/*   Updated: 2024/01/28 10:45:05 by ljustici         ###   ########.fr       */
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

/**
 * Function that spans a token, splits it when it finds quotes and then
 * joins the resulting pieces together in a new token, without said quotes.
 * The quotes that must be trimmed are opening and closing quotes.
 * A quote is opening or closing if it belongs to a pair of quotes.
*/
char *clean_quotes(char *s, char q)
{
    char **clean;
    char *noqts;
    int array_len;
    int i;

    i = 0;
    clean = ft_split(s, q);
    noqts = ft_calloc(1, sizeof(char*));
    array_len = ft_array_len(clean);
    while (i < array_len)
    {
        noqts = ft_join_free(noqts, clean[i]);
        i++;
    }
    ft_free_array(clean);
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
 * Returns position of character q in string token
*/
int quote_pos(char *token, int start, char q)
{
    size_t i;

    i = start;
    while(i < ft_strlen(token))
    {
        if (token[i] == q)
            return(i);
        i++;
    }
    return(i);
}

/*int is_outer_quote_simple(char *token, size_t pos)
{
    int start_s;
    int end_s;
    int start_d;
    int end_d;

    start_s = quote_pos(token, pos, '\'');
    end_s = quote_pos(token, start_s + 1, '\'');
    if (end_s == 0)
        return(0);
    start_d = quote_pos(token, pos, '\"');
    end_d = quote_pos(token, start_d + 1, '\"');
    if (end_d == 0)
        return(1);
    if (start_s < start_d && end_s > end_d)
        return(1);
}*/

int should_clean_quotes(char *token, char **parsed)
{
    size_t i;
	size_t len;
	size_t dqt;
	size_t sqt;

	len = ft_strlen(token);
	dqt = 0;
	sqt = 0;
	i = 0;
    *parsed = ft_strdup(token); 
	while(i < len)
	{
        if (dqt == 2)
			dqt = 0;
        else if (token[i] == '\"' && sqt == 0)
			dqt++;
		if (sqt == 2)
			sqt = 0;
		else if (token[i] == '\'' && dqt == 0)
			sqt++;
        if (dqt == 1 || sqt == 0)
        {
            *parsed = clean_quotes(&(*parsed)[i], '\"');
            return(1);
        }
        else if (dqt == 0 || sqt == 1)
        {
            *parsed = clean_quotes(&(*parsed)[i], '\'');
            return(1);
        }
    }
    return(0);
}

int clean_outer_quotes(char *token, char **parsed)
{
    int start_s;
    int end_s;
    int start_d;
    int end_d;

    if (!has_qts(token, '\'') || !has_qts(token, '\"'))
        return(0);
    start_s = quote_pos(token, 0, '\'');
    end_s = quote_pos(token, start_s + 1, '\'');
    start_d = quote_pos(token, 0, '\"');
    end_d = quote_pos(token, start_d + 1, '\"');
    if (start_s < start_d && end_s > end_d)
    {
        *parsed = clean_quotes(token, '\'');
        return(1);
    }
    else if (start_d < start_s && end_d > end_s)
    {
        *parsed = clean_quotes(token, '\"');
        return(1);
    }
    return(0);
}

/**
 * A token is a variable if it only contains allowed
 * characters and is at least 2 characters long.
 * The variable might be contained inside double quotes,
 * or there might be quoted characters next to the variable,
 * but it can't be contained inside simple quotes.
*/
int is_var(char *token)
{
	size_t len;
	size_t i;
    //size_t j;

    //printf("Entra en is_var %s\n", token);
	i = 0;
	len = ft_strlen(token);
    //printf("len: %zu y c: %c\n", len, token[i]);
    //printf("%zu %c\n",len, token[i]);
	if (len > 1 && token[0] == '$' && (token[1] == '$' 
        || token[1] == '_' || ft_isalnum(token[1]) || token[1] == '?'))
    { 
		span_var_in_dqt(token, &i, len);
        return(1);
    }
    else
        return(0);
    /*printf("Llega aquí\n");
    if (token[i - 2] == '$' && (token[i - 1] == '$' || ft_isdigit(token[i - 1]) //modificar
        || token[i - 1] == '?'))
        return(1);
    if (i == len || token[i] == '\"' || should_split(token[i])
        //|| (!ft_isalnum(token[i]) && token[i] != '\'')
        || (token[i] == '\'' && is_first_quote(token, i, token[i])))
    {
            printf("ENTRA EN IS_VAR ULTIMO CASO %zu %c\n",len, token[i]);
            j = i;
            if (i == len)
                return(1);
            span_tail_str(token, &j);
            span_until_quote(token, &i, '\'');
            if (!token[i] || (token[i] && token[i] != '\''))
                return(1);
            else if (i > j && is_first_quote(token, i, '\''))
                return(1);
    }*/
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
