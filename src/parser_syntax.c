/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:17:57 by ljustici          #+#    #+#             */
/*   Updated: 2023/12/19 14:34:16 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Returns true if there are two consecutive redirections
*/
int is_double_redir(char **args, char **wrong_tk)
{
    int i;
    int n;

    i = 0;
    n = ft_array_len(args);
    while(i < n && n > 1)
    {
        if (is_redir(args[i]))
        {
            if (args[i + 1] && is_redir(args[i + 1]))
            {
                *wrong_tk = args[i + 1];
                return(1);
            }
        }
        i++;
    }
    return(0);
}

/**
 * Returns true if there is any orphan redirection:
 * - the last argument is a redirection
 * - the only argument is a redirection
*/
int is_orphan_redir(char **args)
{
    int n;

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
 * a|
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
    if (ft_strcmp(tokens[0], "|") == 0 || ft_strcmp(tokens[n - 1], "|") == 0)
        error_syntax_token(tokens[0], ERROR_SYNTAX_UNEXPECTED_TOKEN);
    else if (is_double_redir(tokens, &wrong_tk))
        error_syntax_token(wrong_tk, ERROR_SYNTAX_UNEXPECTED_TOKEN);
    else if (is_orphan_redir(tokens))
        error_syntax_token(tokens[n - 1], ERROR_SYNTAX_UNEXPECTED_TOKEN);
    else{
        //printf("No %s\n",tokens[n - 1]);
        is_wrong = 0;
    }
    return(is_wrong);
}
