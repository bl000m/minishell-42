/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/22 11:24:21 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*duplicating_token(char *s, int start, int end)
{
	char	*token;
	int		n_token;

	n_token = 0;
	token = malloc(sizeof(char) * (end - start + 1));
	if (!token)
		return (0);
	while (s[start] && start < end)
		token[n_token++] = s[start++];
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

// needed by expanding_path but to be modified (not called by other func anymore)
int	are_quotes(char c)
{
	if (c == '\"')
		return (2);
	else if (c == '\'')
		return (3);
	return (1);
}
