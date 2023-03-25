/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_counting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:06:45 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/25 14:08:22 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	space_handling(char *s, int *i)
{
	while (s[*i] && s[*i] == ' ')
		*i += 1;
	*i -= 1;
}

void	all_other_handling(char *s, int *n_tokens, int *i)
{
	while (s[*i] && s[*i] != ' ' && s[*i] != '<'
		&& s[*i] != '>' && s[*i] != '|')
	{
		if (s[*i] == '\"')
		{
			*i += 1;
			while (s[*i] != '\"')
				*i += 1;
		}
		*i += 1;
	}
	if (s[*i] != '<' || s[*i] != '>' || s[*i] != '|')
		*i -= 1;
	*n_tokens += 1;
}

void	pipe_redirections_handling(char *s, int *n_tokens, int *i)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		*i += 1;
		*n_tokens += 1;
	}
	else if (s[*i] == '>' && s[*i + 1] == '>')
	{
		*i += 1;
		*n_tokens += 1;
	}
	else if (s[*i] == '|')
	{
		while (s[*i] == '|')
			*i += 1;
		*n_tokens += 1;
	}
	else
		*n_tokens += 1;
}

void identify_token(char *s, char character, int *n_tokens, int *i)
{
	if (character == '<' || character == '>' || character == '|')
		pipe_redirections_handling(s, n_tokens, i);
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
	while (s[i] == ' ')
		i++;
	while (i < size)
	{
		identify_token(s, s[i], n_tokens, &i);
		i++;
	}
	// printf("n.token = %d\n", *n_tokens);
	return (n_tokens);
}
