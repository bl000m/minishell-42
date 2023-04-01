/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathiapagani <mathiapagani@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:03:02 by mpagani           #+#    #+#             */
/*   Updated: 2023/04/01 21:27:19 by mathiapagan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	specific_cases(t_minish *data, int *i, int *res)
{
	if (data->tokens[*i][0] == '.' && !data->tokens[*i][1])
  {
		printf("minishell: .: filename argument required\n");
	  *res = 1;
  }
	else if (data->tokens[*i][0] == '/' && !data->tokens[*i][0])
  {
		printf("minishell: /: Is a directory\n");
	  *res = 1;
  }
	else if (data->tokens[*i][0] == '.'
		&& data->tokens[*i][1] == '/' && !data->tokens[*i][2])
  {
		printf("minishell: ./: Is a directory\n");
	  *res = 1;
  }
	else if (!ft_strncmp(data->tokens[*i], "||", 2))
  {
		printf("syntax error near unexpected token\n");
	  *res = 1;
  }
	return (*res);
}

char	*getting_rid_of_quotes(char *token)
{
	int		i;
	int		j;
	int		quote;
	char	*result;

	i = 0;
	j = 0;
	quote = 0;
	result = ft_calloc(sizeof(char), (int)ft_strlen(token) + 1);
	if (!result)
		return (NULL);
	while (token[i])
	{
		if (are_quotes(token[i]) && !quote)
			quote = are_quotes(token[i++]);
		while (token[i] && (!are_quotes(token[i])
				|| (quote && are_quotes(token[i]) != quote)))
			result[j++] = token[i++];
		if (token[i] && are_quotes(token[i]) == quote)
		{
			quote = 0;
			i++;
		}
	}
	return (result);
}

int	count_token_cmd(t_minish *data, int *i)
{
	int	count;
	int	temp;

	temp = *i;
	count = 0;

	while (data->tokens[temp] && data->tokens[temp][0] != '|'
		&& data->tokens[temp][0] != '\0' && data->tokens[temp][0] != '<'
		&& data->tokens[temp][0] != '>')
	{
		count++;
		temp++;
	}
	return (count);
}

int	cmds_number(t_minish *data)
{
	int		count;
	t_cmd	*ptr;

	count = 0;
	ptr = data->cmds;
	while (ptr)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

int	are_quotes(char c)
{
	if (c == '\"')
		return (1);
	else if (c == '\'')
		return (2);
	return (0);
}
