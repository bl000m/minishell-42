/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 14:32:59 by mpagani          ###   ########.fr       */
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
	*(*token + n_token) = 0;
	return (*token);
}

void	duplicating_with_conditions(char **token, char *s, int start, int end)
{
	int		n_token;
	int		btw_double_quotes;
	int		btw_simple_quotes;

	n_token = 0;
	btw_double_quotes = 0;
	btw_simple_quotes = 0;

	while (s[start] && start < end)
	{
		if (s[start] == '\"' && s[start + 1] != '|'
			&& s[start + 1] != '<' && s[start + 1] != '>')
		{
			btw_double_quotes = 1;
			if (btw_simple_quotes == 0)
				start++;
		}
		if (s[start] == '\'' && btw_double_quotes)
		{
			if (btw_simple_quotes == 1)
				btw_simple_quotes = 0;
			else
				btw_simple_quotes = 1;
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
			*(*token + n_token) = 0;
		else if ((!(btw_simple_quotes == 0
					&& (start > 0 && s[start - 1] == '\''))))
		{
			*(*token + n_token) = s[start];
			n_token++;
		}
		else
		{
			*(*token + n_token) = s[start];
			n_token++;
		}
		start++;
	}
	*(*token + n_token) = 0;
}


char	*duplicating_token(char *s, int start, int end)
{
	char	*token;

	token = malloc(sizeof(char) * ((end - start) + 1));
	if (!token)
		return (0);
	if (ft_memchr(&s[start], '$', end - start)
		|| ft_memchr(&s[start], '~', end - start))
		token = duplicating_dollar(&token, s, start, end);
	else
		duplicating_with_conditions(&token, s, start, end);
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
