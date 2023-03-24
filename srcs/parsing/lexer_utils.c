/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/24 11:39:02 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*duplicating_token(char *s, int start, int end)
{
	char	*token;
	int		n_token;
	int		btw_double_quotes;

	n_token = 0;
	btw_double_quotes = 0;
	token = malloc(sizeof(char) * (end - start + 1));
	if (!token)
		return (0);
	while (s[start] && start < end)
	{
		if (s[start] == '\"')
		{
			btw_double_quotes = 1;
			start++;
		}
		if (s[start] == '\'' && btw_double_quotes == 0)
			start++;
		if (start == end || (s[start] == '\"'))
			token[n_token] = 0;
		else
			token[n_token] = s[start];
		n_token++;
		start++;
	}
	token[n_token] = 0;
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
