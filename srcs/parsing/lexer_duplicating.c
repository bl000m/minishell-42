/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_duplicating.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/02 22:27:12 by mathiapagan      ###   ########.fr       */
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
		return (NULL);
  if (odd_quotes(s))
  {
    printf("An odd number of quotes is not allowed in Minishell.\n");
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

// @Felipe: double_quotes_hanndling twice in function for a reason! not to be modified
void	duplicating_with_conditions(t_minish *data, char **token, char *s)
{
	int		n_token;

	n_token = 0;
	while (s[data->start] && data->start < data->end)
	{
		if (s[data->start] == '\"')
      double_quotes_handling(data, s);
		if (s[data->start] == '\'')
      simple_quotes_handling(data, s);
    if (s[data->start] == '\"')
      double_quotes_handling(data, s);
    *(*token + n_token) = s[data->start];
    n_token++;
		data->start++;
	}
	*(*token + n_token) = 0;
}


void	double_quotes_handling(t_minish *data, char *s)
{
	if (s[data->start + 1] != '\0' && s[data->start + 1] != '|'
		&& s[data->start + 1] != '<' && s[data->start + 1] != '>')
	{
		if (data->btw_double_quotes == 1)
      data->btw_double_quotes = 0;
    else
      data->btw_double_quotes = 1;
		if (data->btw_simple_quotes == 0)
			data->start++;
	}
    else if ((s[data->start - 1] && s[data->start - 1] != '|'
    && s[data->start - 1] != '<' && s[data->start - 1] != '>'
    && s[data->start + 1] == '\0'))
    data->start++;
}

void	simple_quotes_handling(t_minish *data, char *s)
{
  if (data->btw_simple_quotes == 1)
    data->btw_simple_quotes = 0;
  else
    data->btw_simple_quotes = 1;
	if (s[data->start + 1] != '\0' && data->btw_double_quotes == 0
    && s[data->start + 1] != '|' && s[data->start + 1] != '<'
    && s[data->start + 1] != '>')
	{
		data->start++;
		if (s[data->start] == '\'')
			data->btw_simple_quotes = 0;
	}
  else if ((s[data->start + 1] == '\0' && data->btw_double_quotes == 0
    && s[data->start - 1] != '|' && s[data->start - 1] != '<'
    && s[data->start - 1] != '>'))
    data->start++;
}

void  duplicating_dollar(t_minish *data, char **token, char *s)
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

int odd_quotes(char *s)
{
  int i;
  int count_simple;
  int count_double;

  i = 0;
  count_simple = 0;
  count_double = 0;
  while (s[i])
  {
    if (s[i] == '\'')
      count_simple++;
    if (s[i] == '\"')
      count_double++;
    i++;
  }
  if (count_simple % 2 != 0 || count_double % 2 != 0)
    return (1);
  else
    return (0);
}
