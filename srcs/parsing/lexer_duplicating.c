/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_duplicating.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpagani <mpagani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 15:03:58 by mpagani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*duplicating_dollar(t_minish *data, char **token, char *s)
{
	int		n_token;

	n_token = 0;
	while (s[data->start] && data->start < data->end)
	{
		*(*token + n_token) = s[data->start];
		n_token++;
		data->start++;
	}
	*(*token + n_token) = 0;
	return (*token);
}

void	double_quotes_handling(t_minish *data, char *s)
{
	if (s[data->start] == '\"' && s[data->start + 1] != '|'
		&& s[data->start + 1] != '<' && s[data->start + 1] != '>')
	{
		data->btw_double_quotes = 1;
		if (data->btw_simple_quotes == 0)
			data->start++;
	}
}

void	simple_quotes_handling(t_minish *data, char *s)
{
	if (s[data->start] == '\'' && data->btw_double_quotes)
	{
		if (data->btw_simple_quotes == 1)
			data->btw_simple_quotes = 0;
		else
			data->btw_simple_quotes = 1;
	}
	if (s[data->start] == '\'' && s[data->start + 1] != '|'
		&& data->btw_double_quotes == 0
		&& s[data->start + 1] != '<' && s[data->start + 1] != '>')
	{
		if (data->btw_simple_quotes == 1 && s[data->start] == '\'')
			data->btw_simple_quotes = 0;
		else
			data->btw_simple_quotes = 1;
		data->start++;
		if (s[data->start] == '\'')
			data->btw_simple_quotes = 0;
	}
}

void	duplicating_with_conditions(t_minish *data, char **token, char *s)
{
	int		n_token;

	n_token = 0;
	while (s[data->start] && data->start < data->end)
	{
		double_quotes_handling(data, s);
		simple_quotes_handling(data, s);
		if (data->start == data->end || ((s[data->start] == '\"'
					|| s[data->start] == '\'') && s[data->start + 1] == '\0'))
			*(*token + n_token) = 0;
		else
		{
			*(*token + n_token) = s[data->start];
			n_token++;
		}
		data->start++;
	}
	*(*token + n_token) = 0;
}


char	*duplicating_token(t_minish *data, char *s, int start, int end)
{
	char	*token;

	data->start = start;
	data->end = end;
	token = malloc(sizeof(char) * ((end - start) + 1));
	if (!token)
		return (0);
	if (ft_memchr(&s[start], '$', end - start)
		|| ft_memchr(&s[start], '~', end - start))
		token = duplicating_dollar(data, &token, s);
	else
		duplicating_with_conditions(data, &token, s);
	return (token);
}
