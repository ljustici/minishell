/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:32:34 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/15 18:55:18 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
        noqts = ft_strjoin(noqts, clean[i]);
        i++;
    }
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