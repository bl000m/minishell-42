/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_counting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:06:45 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/21 16:25:00 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	double_quote_handling(char *s, int *n_tokens, int *i)
{
	while (s[*i + 1] && s[*i + 1] != '\"')
		*i += 1;
	*n_tokens += 1;
	*i += 2;
}

void	simple_quote_handling(char *s, int *n_tokens, int *i)
{
	while (s[*i + 1] && s[*i + 1] != '\'')
		*i += 1;
	*n_tokens += 1;
	*i += 2;
}

void	space_handling(char *s, int *i)
{
	while (s[*i + 1] && s[*i + 1] != ' ')
		*i += 1;
}

void	all_other_handling(char *s, int *n_tokens, int *i)
{
	while (s[*i + 1] && s[*i + 1] != ' ' && s[*i + 1] != '\'' && s[*i + 1] != '\"')
		*i += 1;
	*n_tokens += 1;
	*i += 1;
}

void identify_token(char *s, char character, int *n_tokens, int *i)
{
	if (character == '\"')
		double_quote_handling(s, n_tokens, i);
	else if (character == '\'')
		simple_quote_handling(s, n_tokens, i);
	else if (character == ' ')
		space_handling(s, i);
	else
		all_other_handling(s, n_tokens, i);
}

int	*tokens_counter(char *s, int *n_tokens)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[size])
		size++;
	while (i < size)
	{
		identify_token(s, s[i], n_tokens, &i);
		i++;
	}
	return (n_tokens);
}