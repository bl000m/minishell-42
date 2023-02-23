/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:29:23 by mpagani           #+#    #+#             */
/*   Updated: 2023/02/22 12:55:14 by mpagani          ###   ########.fr       */
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

void	space_token(char *s, int *start, int *end)
{
	while (s[*end] && s[*end] == ' ')
		*end += 1;
	*start = *end;
}

void	all_other_token(char *s, int *start, int *end)
{
	*start = *end;
	while (s[*end] && s[*end] != ' ' && s[*end] != '\'' && s[*end] != '\"'
			&& s[*end] != '<' && s[*end] != '>' && s[*end] != '|')
		*end += 1;
}

void	pipe_redirections_token(int *start, int *end)
{
	*start = *end;
	*end += 1;
}

void add_token(char *s, int *start, int *end)
{
	if (s[*end] == '\"')
		double_quote_token(s, start, end);
	else if (s[*end] == '\'')
		simple_quote_token(s, start, end);
	else if (s[*end] == '<' || s[*end] == '>' || s[*end] == '|')
		pipe_redirections_token(start, end);
	else if (s[*end] == ' ')
		space_token(s, start, end);
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
	while (data->full_command[end] == ' ')
		end++;
	while (n_token < data->n_tokens)
	{
		add_token(data->full_command, &start, &end);
		if (data->full_command[end -1] != ' ')
		{
			table[n_token] = duplicating_token(data->full_command, start, end);
			if (!table[n_token])
				ft_free(table);
			n_token++;
		}
	}
	return (table);
}
