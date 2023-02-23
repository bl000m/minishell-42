/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelfort <fbelfort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/23 12:30:58 by fbelfort         ###   ########.fr       */
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

int	are_quotes(char c)
{
	if (c == '\"')
		return (1);
	else if (c == '\'')
		return (2);
	return (0);
}
