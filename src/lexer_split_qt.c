/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_qt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:39:05 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/21 20:03:06 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int assign_quoted_token(char **result, const char *s, size_t *i, int *j, int f_letter_pos)
{
	if (s[*i] == '\'' && is_spnltab(s[*i - 1]))
	{
		f_letter_pos = *i;
		span_until_quote(s, i, s[*i]);
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

int assign_doubleqt_token(char **result, const char *s, size_t *i, int *j, int f_letter_pos)
{
    size_t end_qt;
    
    printf("comprueba %c\n", s[*i]);
    if (s[*i] == '\"')
    {
        printf("entra\n");
        end_qt = get_char_pos(s, *i + 1, s[*i]);
        printf(">>>>%zu", end_qt);
        while(*i <= end_qt)
        {
            f_letter_pos = *i;
            while(s[*i] != '$' && *i <= end_qt)
                (*i)++;
            result[*j] = ft_substr(s, f_letter_pos, *i - f_letter_pos);
            printf("1result: [%s] en char %c\n", result[*j], s[*i]);
            (*j)++;
            f_letter_pos = *i;
            if (s[*i] == '$' && s[*i + 1] == '$' && *i <= end_qt)
            {
                result[*j] = ft_substr(s, f_letter_pos, 2);
                (*j)++;
                *i = *i + 2;
            }
            else if (s[*i] == '$' && *i <= end_qt)
            {
                while(*i < end_qt && should_split(s[*i]) == 0)
                    (*i)++;
                result[*j] = ft_substr(s, f_letter_pos, *i - f_letter_pos);
                printf("2result: [%s] en char %c\n", result[*j], s[*i]);
                (*j)++;
            }
            //(*i)++;   
            printf("vuelta en pos %zu\n", *i); 
        }
    }
    printf("sale en pos %zu]\n", *i);
    return(1);
}
