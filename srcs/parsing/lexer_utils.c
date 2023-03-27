/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/27 14:08:23 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*duplicating_dollar(char **token, char *s, int start, int end)
{
	int		n_token;

	n_token = 0;
	while (s[start] && start < end)
	{
		*(*token + n_token) = s[start];
		n_token++;
		start++;
	}
	return (*token);
}

void	duplicating_standard(t_lexer *lex, char **token, char *s, int *start, int *end)
{
	while (s[*start] && *start < *end)
	{
		if (s[*start] == '\'' && lex->btw_double_quotes)
		{
			*token[lex->n_token] = s[*start];
			lex->n_token++;
		}
		if (s[*start] == '\"' && s[*start + 1] != '|'
			&& s[*start + 1] != '<' && s[*start + 1] != '>')
		{
			lex->btw_double_quotes = 1;
			if (lex->btw_simple_quotes == 0)
				*start += 1;
		}
		if (s[*start] == '\'' && s[*start + 1] != '|'
			&& lex->btw_double_quotes == 0
			&& s[*start + 1] != '<' && s[*start + 1] != '>')
		{
			if (lex->btw_simple_quotes == 1 && s[*start] == '\'')
				lex->btw_simple_quotes = 0;
			else
				lex->btw_simple_quotes = 1;
			*start += 1;
			if (s[*start] == '\'')
				lex->btw_simple_quotes = 0;
		}
		if (*start == *end || ((s[*start] == '\"'
					|| s[*start] == '\'') && s[*start + 1] == '\0'))
			*token[lex->n_token] = 0;
		else if ((!(lex->btw_simple_quotes == 0 && s[*start - 1] == '\'')))
		{
			*token[lex->n_token] = s[*start];
			lex->n_token++;
		}
		if (!(lex->btw_simple_quotes == 0 && s[*start - 1] == '\''))
			*start += 1;
	}
}

char	*duplicating_token(t_minish *data, char *s, int start, int end)
{
	char	*token;
	t_lexer	*lex;

	lex = data->lex;
	token = malloc(sizeof(char) * (end - start + 1));
	if (!token)
		return (0);
	if (ft_memchr(&s[start], '$', (end - start))
		|| ft_memchr(&s[start], '~', (end - start)))
		token = duplicating_dollar(&token, s, start, end);
	else
	{
		duplicating_standard(lex, &token, s, &start, &end);
		token[lex->n_token] = 0;
	}
	return (token);
}

char	**ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (0);
}

int	are_quotes(char c)
{
	if (c == '\"')
		return (1);
	else if (c == '\'')
		return (2);
	return (0);
}
