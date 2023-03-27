/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/26 21:42:29 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_if_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*duplicating_dollar(char **token, char *s, int start, int end)
{
	int		n_token;

	n_token = 0;
	// printf("end = %d\n", end);
	while (s[start] && start < end)
	{
		*(*token + n_token) = s[start];
		n_token++;
		start++;
	}
	// printf("token = %s\n", *token);
	return (*token);
}

// char	*duplicating_start_dollar(char **token, char *s, int start, int end)
// {
//   int		n_token;

// 	n_token = 0;
// 	// printf("end = %d\n", end);
// 	while (s[start] && start < end)
// 	{
// 		*(*token + n_token) = s[start];
// 		n_token++;
// 		start++;
// 	}
// 	// printf("token = %s\n", *token);
// 	return (*token);
// }
char	*duplicating_token(char *s, int start, int end)
{
	char	*token;
	int		n_token;
	int		btw_double_quotes;
	int		btw_simple_quotes;

	n_token = 0;
	btw_double_quotes = 0;
	btw_simple_quotes = 0;

	token = malloc(sizeof(char) * (end - start + 1));
	if (!token)
		return (0);
	if (check_if_dollar(s) && s[start] == '\'')
		token = duplicating_dollar(&token, s, start, end);
  else if (s[start] == '$')
    token = duplicating_dollar(&token, s, start, end);
	else
	{
		while (s[start] && start < end)
		{
      // printf("start of while\n");
	    if (check_if_dollar(s) && s[start] == '\'' && btw_double_quotes)
      {
          token[n_token] = s[start];
				  n_token++;
      }
			if (s[start] == '\"' && s[start + 1] != '|'
				&& s[start + 1] != '<' && s[start + 1] != '>')
			{
				printf("start in double= %d\n", start);
				btw_double_quotes = 1;
				// printf("btw_simple_quotes= %d\n", btw_simple_quotes);
				if (btw_simple_quotes == 0)
					start++;
			}
			if (s[start] == '\'' && s[start + 1] != '|' && btw_double_quotes == 0
				&& s[start + 1] != '<' && s[start + 1] != '>')
			{
				printf("start in simple= %d\n", start);
				if (btw_simple_quotes == 1 && s[start] == '\'')
					btw_simple_quotes = 0;
				else
					btw_simple_quotes = 1;
				start++;
				if (s[start] == '\'')
					btw_simple_quotes = 0;
			}
			if (start == end
				|| ((s[start] == '\"' || s[start] == '\'') && s[start + 1] == '\0'))
        {
          printf("in start = end\n");
				  token[n_token] = 0;
        }
			else if ((!(btw_simple_quotes == 0 && s[start - 1] == '\'')))
			{
        printf("in last else if\n");
				token[n_token] = s[start];
				n_token++;
			}
			// printf("start before last if = %d\n", start);
			// printf("btw_simple_quotes = %d\n", btw_simple_quotes);
			if (!(btw_simple_quotes == 0 && s[start - 1] == '\''))
      {
				start++;
        printf("start in last last: %d\n", start);
      }
			// printf("start after last if = %d\n", start);
		}
		token[n_token] = 0;
	}
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
