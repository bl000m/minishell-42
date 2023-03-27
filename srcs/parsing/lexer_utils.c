/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/27 13:06:31 by mpagani          ###   ########.fr       */
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

char	*duplicating_token(char *s, int start, int end)
{
	char	*token;
	int		n_token;
	int		btw_double_quotes;
	int		btw_simple_quotes;

	n_token = 0;
	btw_double_quotes = 0;
	btw_simple_quotes = 0;

	token = malloc(sizeof(char) * (end - start + 1));
	if (!token)
		return (0);
	if (ft_memchr(&s[start], '$', end - start))
		token = duplicating_dollar(&token, s, start, end);
	else if (s[start] == '$')
		token = duplicating_dollar(&token, &s[start], start, end);
	else
	{
		while (s[start] && start < end)
		{
			if (s[start] == '\'' && btw_double_quotes)
			{
				token[n_token] = s[start];
				n_token++;
			}
			if (s[start] == '\"' && s[start + 1] != '|'
				&& s[start + 1] != '<' && s[start + 1] != '>')
			{
				btw_double_quotes = 1;
				if (btw_simple_quotes == 0)
					start++;
			}
			if (s[start] == '\'' && s[start + 1] != '|'
				&& btw_double_quotes == 0
				&& s[start + 1] != '<' && s[start + 1] != '>')
			{
				if (btw_simple_quotes == 1 && s[start] == '\'')
					btw_simple_quotes = 0;
				else
					btw_simple_quotes = 1;
				start++;
				if (s[start] == '\'')
					btw_simple_quotes = 0;
			}
			if (start == end || ((s[start] == '\"'
						|| s[start] == '\'') && s[start + 1] == '\0'))
				token[n_token] = 0;
			else if ((!(btw_simple_quotes == 0 && s[start - 1] == '\'')))
			{
				token[n_token] = s[start];
				n_token++;
			}
			if (!(btw_simple_quotes == 0 && s[start - 1] == '\''))
				start++;
		}
		token[n_token] = 0;
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
