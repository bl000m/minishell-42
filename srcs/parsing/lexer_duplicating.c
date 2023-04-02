/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_duplicating.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/02 16:52:08 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*duplicating_token(t_minish *data, char *s, int start, int end)
{
	char	*token;

	data->start = start;
	data->end = end;
	token = malloc(sizeof(char) * ((end - start) + 1));
	if (!token)
		hard_exit(data, NULL, NULL);
	if (odd_quotes(s))
	{
		error_manager(0, EC_ODDQUOTES, NULL, EXIT_FAILURE);
		data->lexer_error = 1;
		return (NULL);
	}
	if (ft_memchr(&s[start], '$', end - start)
		|| ft_memchr(&s[start], '~', end - start))
		duplicating_dollar(data, &token, s);
	else
		duplicating_with_conditions(data, &token, s);
	return (token);
}

void	duplicating_with_conditions(t_minish *data, char **token, char *s)
{
	int		n_token;

	n_token = 0;
	while (s[data->start] && data->start < data->end)
	{
		if (s[data->start] == '\"')
			double_quotes_handling(data);
		if (s[data->start] == '\'')
			simple_quotes_handling(data, s);
		if (s[data->start] == '\"')
			double_quotes_handling(data);
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

void	double_quotes_handling(t_minish *data)
{
	if (data->btw_double_quotes == 1)
		data->btw_double_quotes = 0;
	else
		data->btw_double_quotes = 1;
	if (data->btw_simple_quotes == 0)
		data->start++;
}

void	simple_quotes_handling(t_minish *data, char *s)
{
	if (data->btw_simple_quotes == 1)
		data->btw_simple_quotes = 0;
	else
		data->btw_simple_quotes = 1;
	if (data->btw_double_quotes == 0)
	{
		data->start++;
		if (s[data->start] == '\'')
			data->btw_simple_quotes = 0;
	}
}

void	duplicating_dollar(t_minish *data, char **token, char *s)
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
}
