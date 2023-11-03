/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_qt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:39:05 by ljustici          #+#    #+#             */
/*   Updated: 2023/11/03 18:53:18 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int assign_quoted_token(char **result, const char *s, size_t *i, int *j, int f_letter_pos)
{
	if (s[*i] == '\'' && (is_spnltab(s[*i - 1]) || *i == 0))
	{
		f_letter_pos = *i;
		span_until_quote(s, i, s[*i]);
        if (should_split(s[*i]) == 0)
        {
            while(s[*i] && should_split(s[*i]) == 0)
                (*i)++;
        }
		result[*j] = ft_substr(s, f_letter_pos, (*i - f_letter_pos) + 1);
		printf("[j: %i --> %s]\n", *j, result[*j]);
		if(!result[*j])
			return(0); //malloc error
		*j = *j + 1;
		*i = *i + 1;
	}
	return(1);
}

int get_char_pos(const char *s, size_t start, char c)
{
    size_t i;
    
    i = start;
    while(s[i] && s[i] != c)
        i++;
    return(i);
}

void span_var_in_dqt(const char *s, size_t *i, size_t end_qt)
{
    (*i)++;
    if (s[*i] == '$' || ft_isdigit(s[*i]) || s[*i] == '?')
    {
        (*i)++;
        return ;
    }
    while(*i < end_qt && (ft_isalnum(s[*i]) == 1 || s[*i] == '_'))
        (*i)++;
}

//TODO: convertir funcion en int para proteger malloc
void add_token(const char *s, char **result, int f_letter_pos, size_t i, int *j)
{
    if (i - f_letter_pos > 0)
    {
        result[*j] = ft_substr(s, f_letter_pos, i - f_letter_pos);
        //if (!result[*j])
		//    return (0);
        (*j)++;
    }
    else
        printf("NO tamaño\n");
}

int assign_doubleqt_token(char **result, const char *s, size_t *i, int *j, int f_letter_pos)
{
    size_t end_qt;
    
    if (s[*i] == '\"' && (is_spnltab(s[*i - 1]) || *i == 0))
    {
        end_qt = get_char_pos(s, *i + 1, s[*i]);
        while(*i <= end_qt)
        {
            f_letter_pos = *i;
            if (is_var_in_dqt(s, *i) && *i <= end_qt)
            {
                span_var_in_dqt(s, i, end_qt);
                add_token(s, result, f_letter_pos, *i, j);
            }
            else if (*i <= end_qt)
            {
                while(s[*i] && !is_var_in_dqt(s, *i) && *i <= end_qt)
                    (*i)++;
                span_tail_str(s, i);
                add_token(s, result, f_letter_pos, *i, j);
            } 
        }
    }
    return(1);
}
