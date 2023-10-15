/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:35:48 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/15 16:21:27 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_spnltab(char c)
{
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
    while(s[*i] != quote)
        *i = *i + 1;
}

