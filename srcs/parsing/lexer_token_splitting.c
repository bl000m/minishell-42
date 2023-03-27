/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_splitting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:29:23 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/27 13:48:54 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	space_token(char *s, int *start, int *end)
{
	while (s[*end] && s[*end] == ' ')
		*end += 1;
	*start = *end;
}

void	all_other_token(char *s, int *start, int *end)
{
	*start = *end;
	while (s[*end] && s[*end] != ' ' && s[*end] != '<'
		&& s[*end] != '>' && s[*end] != '|')
	{
		if (s[*end] == '\"')
		{
			*end += 1;
			while (s[*end] != '\"')
				*end += 1;
			// break ;
		}
		if (s[*end] == '\'')
		{
			*end += 1;
			while (s[*end] != '\'')
				*end += 1;
			// break ;
		}
		*end += 1;
		// printf("start in simple quote %d\n", *start);
		// printf("end in simple quote %d\n", *end);
	}
	// printf("end = %d\n", *end);
}

void	pipe_redirections_token(char *s, int *start, int *end)
{
	if (s[*end] == '<' && s[*end + 1] == '<')
	{
		*start = *end;
		*end += 2;
	}
	else if (s[*end] == '>' && s[*end + 1] == '>')
	{
		*start = *end;
		*end += 2;
	}
	else if (s[*end] == '|')
	{
		*start = *end;
		while (s[*end] == '|')
			*end += 1;
	}
	else
	{
		*start = *end;
		*end += 1;
	}
}

void add_token(char *s, int *start, int *end)
{
	if (s[*end] == '<' || s[*end] == '>' || s[*end] == '|')
		pipe_redirections_token(s, start, end);
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
	while (data->input[end] == ' ')
		end++;
	while (n_token < data->n_tokens)
	{
		add_token(data->input, &start, &end);
		if (data->input[end -1] != ' ')
		{
			// printf("start = %d\n", start);
			// printf("end = %d\n", end);
			table[n_token] = duplicating_token(data, data->input, start, end);
			if (!table[n_token])
				ft_free(table);
			n_token++;
		}
	}
	return (table);
}
