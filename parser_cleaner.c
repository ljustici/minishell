/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:54:12 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/10 19:34:34 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_active_section(char token_char, size_t *dqt, size_t *sqt,
		size_t *nqt)
{
	if (token_char == '\"' && *sqt == 0)
	{
		(*dqt)++;
		*nqt = 0;
	}
	else if (token_char == '\'' && *dqt == 0)
	{
		(*sqt)++;
		*nqt = 0;
	}
	if (*dqt == 0 && *sqt == 0 && *nqt == 0)
		*nqt = 1;
}

static void	double_qts_section(char *token, char **parsed, size_t *dqt,
		size_t *i)
{
	int	end;
	int	len;
	char *section;

	len = ft_strlen(token);
	end = next_qt_pos(token, (*i) + 1, len, '\"');
	section = clean_quotes(token, '\"', *i, end);
	*parsed = ft_strjoin_free(*parsed, section);
	free(section);
	//printf("parsed: [%s]  y i %zu  y end %d\n", *parsed, *i, end);
	*i = end;
	*dqt = 0;
}

static void	simple_qts_section(char *token, char **parsed, size_t *sqt,
		size_t *i)
{
	int	end;
	int	len;
	char *section;

	len = ft_strlen(token);
	end = next_qt_pos(token, (*i) + 1, len, '\'');
	section = clean_quotes(token, '\'', *i, end);
	*parsed = ft_strjoin_free(*parsed, section);
	free(section);
	//printf("parsed: %s  y i %zu  y end %d\n", *parsed, *i, end);
	*i = end;
	*sqt = 0;
}

static void	no_qts_section(char *token, char **parsed, size_t *nqt, size_t *i)
{
	int	end;
	int	other;
	int	len;
	char *section;

	//printf("Entra en no qts section\n");
	len = ft_strlen(token);
	end = next_qt_pos(token, *i, len, '\'');
	other = next_qt_pos(token, *i, len, '\"');
	if (other < end)
		end = other;
	//printf("end : %d  e i: %zu\n", end, *i);
	section = ft_substr(token, *i, (end - *i));
	*parsed = ft_strjoin_free(*parsed, section);
	free(section);
	section = NULL;
	//printf("new parsed %s\n", *parsed);
	*i = end - 1;
	nqt = 0;
}

void	quote_section_cleaner(char *token, char **parsed, size_t len)
{
	size_t	i;
	size_t	dqt;
	size_t	sqt;
	size_t	nqt;

	dqt = 0;
	sqt = 0;
	nqt = 0;
	i = 0;
	*parsed = NULL;
	//printf("len %zu\n",  len);
	while (i < len)
	{
		//printf("Dentro de quote section cleaner %s y len %zu\n", token, len);
		set_active_section(token[i], &dqt, &sqt, &nqt);
		if (dqt == 1 && sqt == 0)
			double_qts_section(token, parsed, &dqt, &i);
		else if (dqt == 0 && sqt == 1)
			simple_qts_section(token, parsed, &sqt, &i);
		else if (dqt == 0 && sqt == 0 && nqt == 1)
			no_qts_section(token, parsed, &nqt, &i);
		i++;
	}
}

/**
 * Whole function:
 * int		should_clean_quotes(char *token, char **parsed, size_t len)
{
	size_t	i;
	size_t	dqt;
	size_t	sqt;
	size_t	nqt;
	int		end;
	int		end;
	int		end;
	int		other;

	dqt = 0;
	sqt = 0;
	nqt = 0;
	i = 0;
	*parsed = NULL;
	if (!has_qts(token, '\'') && !has_qts(token, '\"'))
		*parsed = ft_strdup(token);
	else
		while (i < len)
		{
			if (token[i] == '\"' && sqt == 0)
			{
				dqt++;
				nqt = 0;
			}
			else if (dqt == 0 && sqt == 0 && nqt == 0)
				nqt = 1;
			if (token[i] == '\'' && dqt == 0)
			{
				sqt++;
				nqt = 0;
			}
			if (dqt == 1 && sqt == 0)
			{
				end = next_qt_pos(token, i + 1, len, '\"');
				*parsed = ft_strjoin_free(*parsed, clean_quotes(token, '\"', i,
							end));
				printf("parsed: %s  y i %zu  y end %d\n",*parsed, i, end);
				i = end;
				dqt = 0;
			}
			else if (dqt == 0 && sqt == 1)
			{
				end = next_qt_pos(token, i + 1, len, '\'');
				*parsed = ft_strjoin_free(*parsed, clean_quotes(token, '\'', i,
							end));
				printf("parsed: %s  y i %zu  y end %d\n",*parsed, i, end);
				i = end;
				sqt = 0;
			}
			else if (dqt == 0 && sqt == 0 && nqt == 1)
			{
				end = next_qt_pos(token, i, len, '\'');
				other = next_qt_pos(token, i, len, '\"');
				if (other < end)
					end = other;
				printf("end : %d  e i: %zu\n", end, i);
				*parsed = ft_strjoin_free(*parsed, ft_substr(token, i, (end
								- i)));
				printf("new parsed %s\n", *parsed);
				i = end - 1;
				nqt = 0;
			}
			i++;
		}	
	return (0);
}

 * Function that spans a token, splits it when it finds quotes and then
 * joins the resulting pieces together in a new token, without said quotes.
 * The quotes that must be trimmed are opening and closing quotes.
 * A quote is opening or closing if it belongs to a pair of quotes.
*
char	*clean_quotes(char *s, char q)
{
	char	**clean;
	char	*noqts;
	int		array_len;
	int		i;

	i = 0;
	clean = ft_split(s, q);
	noqts = ft_calloc(1, sizeof(char *));
	array_len = ft_array_len(clean);
	while (i < array_len)
	{
		noqts = ft_join_free(noqts, clean[i]);
		i++;
	}
	ft_free_array(clean);
	return (noqts);
}
*/