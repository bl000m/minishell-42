/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:29:23 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/21 16:17:24 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	double_quote_token(char *s, int *start, int *end)
{
	*start = *end;
	while (s[*end + 1] && s[*end + 1] != '\"')
		*end += 1;
	*end += 2;
}

void	simple_quote_token(char *s, int *start, int *end)
{
	*start = *end;
	while (s[*end + 1] && s[*end + 1] != '\'')
		*end += 1;
	*end += 2;
}

void	space_token(char *s, int *end)
{
	while (s[*end + 1] && s[*end + 1] != ' ')
		*end += 1;
}

void	all_other_token(char *s, int *start, int *end)
{
	*start = *end;
	while (s[*end + 1] && s[*end + 1] != ' ' && s[*end + 1] != '\'' && s[*end + 1] != '\"')
		*end += 1;
	*end += 1;
}

void add_token(char *s, int *start, int *end)
{
	if (s[*end] == '\"')
		double_quote_token(s, start, end);
	else if (s[*end] == '\'')
		simple_quote_token(s, start, end);
	else if (s[*end] == ' ')
		space_token(s, end);
	else
		all_other_token(s, start, end);
}

char	**tokens_table_filling(t_minish *data, char **table)
{
	int	start;
	int	end;
	int	n_token;

	start = 0;
	end = 0;
	n_token = 0;
	while (n_token < data->n_tokens)
	{
		add_token(data->full_command, &start, &end);
		table[n_token] = duplicating_token(data->full_command, start, end);
		if (!table[n_token])
			ft_free(table);
		n_token++;
		end++;
	}
	return (table);
}
