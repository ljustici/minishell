/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:17:57 by ljustici          #+#    #+#             */
/*   Updated: 2023/12/02 17:10:53 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_double_redir(char **args, char **wrong_tk)
{
    int i;
    int n;

    i = 0;
    n = ft_array_len(args);
    while(i < n)
    {
        if (is_redir(args[i]))
        {
            if (n == 1)
            {
                *wrong_tk = args[i];
                return(1);
            }
            else if (is_redir(args[i + 1]))
            {
                *wrong_tk = args[i + 1];
                return(1);
            }
        }
        i++;
    }
    return(0);
}

int is_last_redir(char **args)
{
    int i;
    int n;

    i = 0;
    n = ft_array_len(args);
    if (is_redir(args[n - 1]))
        return(1);
    return(0);
}

/**
 * |
 * <
 * ||||
 * <<<<<
 * |a
 * change order of commands when needed
*/
int check_token_syntax(char **tokens)
{
    int n;
    int is_wrong;
    char *wrong_tk;

    wrong_tk = NULL;
    is_wrong = 1;
    n = ft_array_len(tokens);
    if (ft_strcmp(tokens[0], "|") == 0)
        error_syntax_token(tokens[0], ERROR_SYNTAX_UNEXPECTED_TOKEN);
    else if (is_double_redir(tokens, &wrong_tk))
        error_syntax_token(wrong_tk, ERROR_SYNTAX_UNEXPECTED_TOKEN);
    else if (is_last_redir(tokens))
        error_syntax_token(tokens[n - 1], ERROR_SYNTAX_UNEXPECTED_TOKEN);
    else{
        printf("No %s\n",tokens[n - 1]);
        is_wrong = 0;
    }
    return(is_wrong);
}