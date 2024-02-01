/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:53:24 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/01 20:35:15 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_pid(char *token)
{
	if (ft_strcmp(token, "$$") == 0)
		return (getpid());
	return (0);
}

/**
 * TODO: reconocer variables especiales
*/
char	*find_var_in_envp(char *var, t_env_lst *envp)
{
	char	*result;

	result = NULL;
	while (envp)
	{
		//printf("- envp name: %s y var: %s\n", envp->nm, var);
		if (ft_strcmp(var, envp->nm) == 0)
		{
			result = ft_strdup(envp->val);
			//printf("result: %s y name: %s\n", result, envp->nm);
			free(var);
			break ;
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
char	*var_expansion(char *token, t_msh *data, size_t *i)
{
	char	*expanded;
	char	*formatted;
	int		start;
	size_t	end;

	expanded = NULL;
	formatted = NULL;
	start = *i;
	end = get_end_of_var(&token[start]);
	expanded = ft_substr(token, start + 1, end - 1);
	if (ft_strcmp(expanded, "?") == 0)
	{
		free(expanded);
		expanded = ft_itoa(data->exit_code);
	}
	else
		expanded = find_var_in_envp(expanded, data->env_lst);
	end = end + start;
	formatted = format_expansion_token(token, expanded, end, start);
	*i += ft_strlen(expanded);
	free(expanded);
	free(token);
	return (formatted);
}

void	set_active_quote(char exp, size_t *dqt, size_t *sqt)
{
	if (*dqt == 2)
		*dqt = 0;
	if (*sqt == 2)
		*sqt = 0;
	if (exp == '\"' && *sqt == 0)
		(*dqt)++;
	if (exp == '\'' && *dqt == 0)
		(*sqt)++;
}

/**
 * Expands the variable inside a token, if any. Otherwise the 
 * token stays the same.
*/
void	set_expanded_token(char **expanded, char *token, t_msh *data)
{
	size_t	i;
	size_t	len;
	size_t	dqt;
	size_t	sqt;

	*expanded = ft_strdup(token);
	len = ft_strlen(*expanded);
	dqt = 0;
	sqt = 0;
	i = 0;
	while (i < len)
	{
		set_active_quote((*expanded)[i], &dqt, &sqt);
		if (is_var(&(*expanded)[i]) && (dqt == 1 || sqt == 0))
			*expanded = var_expansion(*expanded, data, &i);
		else
			i++;
		len = ft_strlen(*expanded);
	}
}

/**
 * Spans the token array and expand variables, if any.
*/
char	**expanding_loop(char **tokens, t_msh *data)
{
	int		i;
	int		j;
	int		len;
	char	**expanded;

	i = 0;
	j = 0;
	len = ft_array_len(tokens);
	expanded = (char **)ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		set_expanded_token(&expanded[j], tokens[i], data);
		i++;
		if (expanded[j])
			j++;
	}
	expanded[j] = 0;
	return (expanded);
}
