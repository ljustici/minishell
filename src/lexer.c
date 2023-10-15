/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:11:36 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/15 17:10:25 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Process quotes
//split line in tokens

int check_open_quote(char *line, char *first, int *i)
{
    int is_opening;
    
    is_opening = 0;
    if (*i == -1 || line[*i])
        (*i)++;
    else
        return (is_opening);
    while(line[*i])
    {
        printf("char: %c i: %i\n", line[*i], *i);
        if ((line[*i] == '\'' || line[*i] == '\"') && *first == -1)
        {
            is_opening = 1;
            *first = line[*i];
            break;
        }
        (*i)++;
    }
    printf("first: %c i: %i\n", *first, *i);
    return(is_opening);
}

int check_closing_quote(char *line, char *first, int *i)
{
    int is_closing;

    is_closing = 0;
    if (!line[*i])
        return (is_closing);
    while(line[(*i)++])
    {
        if (line[*i] == *first)
        {
            printf("Closing encontrada\n");
            is_closing = 1;
            break;
        }
    }
    printf("closing i: %i\n", *i);
    return (is_closing);
}

int check_quotes(char *line)
{
    char first;
    int pair;
    int i;

    i = -1;
    first = -1;
    pair = 0;
    printf("line: [%s], strlen: %zu\n", line, ft_strlen(line));
    while(i == -1 || line[i])
    {
        printf("pair: %i\n", pair);
        pair = check_open_quote(line, &first, &i);
        if (pair == 1 || pair % 2 != 0)
            pair = pair + check_closing_quote(line, &first, &i);
        printf("end loop pair: %i\n", pair);
        first = -1;
    }
    printf("check quotes return: %i\n", pair);
    if (pair % 2 == 0)
        return(0);
    return(1);
}

char **split_line(char *line)
{
    char **tokens = NULL;
    if (check_quotes(line) != 0)
        return(NULL); //error
    tokens = split_by_metachar(line);
    return(tokens);
}

int main()
{
    char line[] ="       lsasd > a.txt |||ab\'dfsdf\'aa|  \"hola $dfdsfa\"\0";
    char **result;
    int i = 0;

    result = split_line(line);
    if (!result)
    {
        printf("aqui");
        return(-1);
    }
    while(result[i])
    {
        printf("%s\n", result[i]);
        i++;
    }
}

//"asds ' ' ' assad" --> correcto

/*
getopts

getopts processes the positional parameters of the parent command. In bash, this is stored in the shell variable "$@". 
So, if you run this command:

mycmd -a argument1 -b argument2

During the time that mycmd is running, the variable $@ contains the string "-a argument1 -b argument2". 
You can use getopts to parse this string for options and arguments.

Every time you run getopts, it looks for one of the options defined in optstring. If it finds one, it places 
the option letter in a variable named optname. If the option does not match those defined in optstring, getopts 
sets variable optname to a question mark ("?").
*/