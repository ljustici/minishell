/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:53:24 by ljustici          #+#    #+#             */
/*   Updated: 2024/01/24 18:08:48 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand_pid(char *token)
{
    if (ft_strcmp(token, "$$") == 0)
        return(getpid());
    return(0);
}

/**
 * TODO: reconocer variables especiales
*/
char	*find_var_in_envp(char *var, t_env_lst *envp)
{
	char	*result;

	result = NULL;
    while(envp)
    {
		printf("- envp name: %s y var: %s\n", envp->nm, var);
        if (ft_strcmp(var, envp->nm) == 0)
		{
			result = ft_strdup(envp->val);
			printf("result: %s y name: %s\n", result, envp->nm);
			free(var);
			break;
		}
        envp = envp->nx;
    }
    return (result);
}

/**
 * Variables need to be replaced by their content, unless they are literals that
 * look like variables:
 * - variables inside simple quotes
 * - dollars followed by a quote then by characters
 * They must be checked before cleaning quotes from tokens.
*/
char *var_expansion(char *token, t_env_lst *envp, size_t *i)
{
	char *expanded;
	char *formatted;
	int start;
	size_t end;

	expanded = NULL;
	formatted = NULL;
	start = *i;

	end = get_end_of_var(&token[start]);
	
	expanded = ft_substr(token, start + 1, end - 1);
	printf("Expanded: [%s]\n", expanded);
	expanded = find_var_in_envp(expanded, envp);
	end = end + start; //TODO: end changes after expansion acording to the expanded word's length
	printf("La variable es %s y start es: %i y end: %zu\n", expanded, start, end);
	formatted = format_expansion_token(token, expanded, end, start);
	*i += ft_strlen(expanded);
	free(expanded);
	expanded = NULL;
	printf("i: %zu\n", *i);
	return(formatted);
}

/**
 * Expands the variable inside a token, if any. Otherwise the token stays
 * the same.
*/
void set_expanded_token(char **expanded, char *token, t_env_lst *envp)
{
	size_t i;
	size_t len;

	i = 0;
	*expanded = ft_strdup(token);
	len = ft_strlen(*expanded);
	while(i < len)
	{
		printf("expanded %s: %zu\n", *expanded, i);
		if (is_var(&(*expanded)[i]))
		{
			printf("Es var\n");
			*expanded = var_expansion(*expanded, envp, &i);
			printf("Se expande a %s\n",*expanded);
		}
		else{
			printf("No es var\n");
		i++;}
		len = ft_strlen(*expanded);
	}
	if (!(*expanded)) //if(*expanded == 0)
		*expanded = ft_strdup(token);
}

/**
 * Spans the token array and expand variables, if any.
*/
char **expanding_loop(char **tokens, t_env_lst *envp)
{
	int i;
	int j;
	int len;
	char **expanded;

	i = 0;
	j = 0;
	len = ft_array_len(tokens);
	expanded = (char **)ft_calloc(len + 1, sizeof(char *));
	while(i < len)
	{
		set_expanded_token(&expanded[j], tokens[i], envp);
		i++;
		if (expanded[j])
			j++;
		/*else
		{
			free(expanded[j]);
			expanded[j] = NULL;
		}*/
	}
	expanded[j] = 0;
	ft_free_array(tokens);
	return(expanded);
}
