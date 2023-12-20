/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:35:48 by ljustici          #+#    #+#             */
/*   Updated: 2023/12/20 18:21:09 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_spnltab(char c)
{
    if (!c)
        return(1);
    if (c == ' ' || c == '\t' || c == '\n')
        return(1);
    return(0);
}

int is_metacharacter(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return(1);
    return(0);
}

int should_split(char c)
{
    if (is_spnltab(c) == 1 || is_metacharacter(c) == 1)
        return(1);
    return(0);
}

void span_until_quote(const char *s, unsigned long *i, char quote)
{
    *i = *i + 1;
    while(s[*i] && s[*i] != quote)
        *i = *i + 1;
}

int is_valid_char_in_var(char c)
{
    if (ft_isalnum(c) == 0 && c != '_' && c != '?')
        return(0);
    return(1);
}
