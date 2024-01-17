/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:11:36 by ljustici          #+#    #+#             */
/*   Updated: 2024/01/17 16:25:11 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_open_quote(char *line, char *first, int *i)
{
    int is_opening;
    
    is_opening = 0;
    if (*i == -1 || line[*i])
        (*i)++;
    else
        return (is_opening);
    while(line[*i] && (*i < (int)ft_strlen(line)))
    {
        if (line[*i] == '\'' || line[*i] == '\"')
        {
            is_opening = 1;
            *first = line[*i];
            break;
        }
        (*i)++;
    }
    //printf("first: %c i: %i\n", *first, *i);
    return(is_opening);
}

int check_closing_quote(char *line, char *first, int *i)
{
    int is_closing;

    is_closing = 0;
    if (!line[*i])
        return (is_closing);
    while(line[(*i)++] && (*i < (int)ft_strlen(line)))
    {
        if (line[*i] == *first)
        {
            //printf("Closing encontrada\n");
            is_closing = 1;
            break;
        }
    }
    //printf("closing i: %i\n", *i);
    return (is_closing);
}

int check_quotes(char *line)
{
    char first;
    int pair;
    int i;

    i = -1;
    first = '\0';
    pair = 0;
    //printf("line: [%s], strlen: %zu\n", line, ft_strlen(line));
    while((i == -1 || line[i]) && (i < (int)ft_strlen(line)) )
    {
        //printf("pair: %i\n", pair);
        pair = check_open_quote(line, &first, &i);
        if (pair == 1 || pair % 2 != 0)
            pair = pair + check_closing_quote(line, &first, &i);
        //printf("end loop pair: %i\n", pair);
        first = '\0';
    }
    //printf("check quotes return: %i\n", pair);
    if (pair % 2 == 0)
        return(0);
    return(1);
}

char **split_line(char *line, t_msh *data)
{
    char **tokens = NULL;
    if (check_quotes(line) != 0)
    {
        error_syntax_token(data, "", ERROR_QUOTE);
        return(NULL);
    }
    tokens = split_by_metachar(line, data);
    return(tokens);
}

void ft_lexer(t_msh *data)
{
    char **result;
    
    result = split_line(data->pipeline, data);
    if (!result)
    {
        error_syntax_token(data, "", ERROR_MALLOC_ERROR);
        return ;
    }
    ft_parse(result, data);
}
