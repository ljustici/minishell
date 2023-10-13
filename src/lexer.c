/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:11:36 by ljustici          #+#    #+#             */
/*   Updated: 2023/10/13 19:55:26 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//Process quotes
//split line in tokens

int check_quotes(char *line)
{
    int i;
    int quot_s;
    int quot_d;

    i = 0;
    quot_s = 0;
    quot_d = 0;
    while(line[i])
    {
        if (line[i] == '\'')
            quot_s++;
        else if (line[i] == '\"')
            quot_d++;
        i++;
    }
    if (quot_s % 2 == 0 && quot_d % 2 == 0)
        return (0);
    return(1);
}

char **split_line(char *line)
{
    char **tokens;
    if (check_quotes(line) != 0)
        return(NULL); //error
    tokens = split_by_metachar(line);
    //perform expansions
    return(tokens);
}


int main()
{
    char line[] ="ls foo '-la | dfsdf' < $var";
    char **result;
    int i = 0;

    result = split_line(line);
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