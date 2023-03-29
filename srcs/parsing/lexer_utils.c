/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:34:55 by mpagani           #+#    #+#             */
/*   Updated: 2023/03/29 14:36:39 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char	*duplicating_dollar(char **token, char *s, int start, int end)
{
	int		n_token;

	n_token = 0;
	while (s[start] && start < end)
	{
		*(*token + n_token) = s[start];
		n_token++;
		start++;
	}
	*(*token + n_token) = 0;
	return (*token);
}

char	*duplicating_token(char *s, int start, int end)
{
	char	*token;
	int		n_token;
	int		btw_double_quotes;
	int		btw_simple_quotes;

	n_token = 0;
	btw_double_quotes = 0;
	btw_simple_quotes = 0;

	token = malloc(sizeof(char) * ((end - start) + 1));
	if (!token)
		return (0);
	if (ft_memchr(&s[start], '$', end - start)
		|| ft_memchr(&s[start], '~', end - start))
		token = duplicating_dollar(&token, s, start, end);
	else
	{
		while (s[start] && start < end)
		{
			if (s[start] == '\"' && s[start + 1] != '|'
				&& s[start + 1] != '<' && s[start + 1] != '>')
			{
        // printf("jump in double in start = %d\n", start);
				btw_double_quotes = 1;
				if (btw_simple_quotes == 0)
					start++;
			}
			if (s[start] == '\'' && btw_double_quotes)
			{
        if (btw_simple_quotes == 1)
        {
          // printf("btw 1 s[start] %c and start = %d\n", s[start], start);
					btw_simple_quotes = 0;
				  // token[n_token] = s[start];
        }
				else
        {
          // printf("btw 0 s[start] %c and start = %d\n", s[start], start);
					btw_simple_quotes = 1;
        }
				// n_token++;
			}
			if (s[start] == '\'' && s[start + 1] != '|'
				&& btw_double_quotes == 0
				&& s[start + 1] != '<' && s[start + 1] != '>')
			{
				if (btw_simple_quotes == 1 && s[start] == '\'')
					btw_simple_quotes = 0;
				else
					btw_simple_quotes = 1;
        // printf("jump in simple in stqrt = %d\n", start);
				start++;
				if (s[start] == '\'')
					btw_simple_quotes = 0;
			}
			if (start == end || ((s[start] == '\"'
						|| s[start] == '\'') && s[start + 1] == '\0'))
      {
        // printf("adding 0 after %c in start = %d new char %d\n", s[start - 1], start, n_token);
				token[n_token] = 0;
      }
			else if ((!(btw_simple_quotes == 0
						&& (start > 0 && s[start - 1] == '\''))))
			{
        // printf("duplicating %c in start = %d and new char = %d and SQ = %d\n", s[start], start, n_token, btw_simple_quotes);
				token[n_token] = s[start];
				n_token++;
			}
      else
      {
        // printf("@ duplicating %c in start = %d and new char = %d and SQ = %d\n", s[start], start, n_token, btw_simple_quotes);
				token[n_token] = s[start];
				n_token++;
        // start++;
			}
			start++;
      // printf("final start %d\n", start);
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
